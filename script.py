#!/usr/bin/env python3
import sys
import yaml
import click
from pathlib import Path
from typing import Any, Dict, List, Optional,   Tuple, Set
from pydantic import BaseModel, Field, field_validator, model_validator
from jinja2 import Environment, FileSystemLoader

# ----------------------------- Models ---------------------------------------

class Conventions(BaseModel):
    precedence: Dict[str, Any] = {}
    assoc_values: Optional[List[str]] = None

class OperatorSpec(BaseModel):
    # Either 'lit' (single lexeme) or 'tokens' (multi-token op like ternary "? :")
    lit: Optional[str] = None
    tokens: Optional[List[str]] = None
    precedence: int
    assoc: str  # "left" | "right" | "none"
    arity: Optional[int] = None
    fixity: Optional[str] = "infix"  # "prefix" | "postfix" | "infix" | "ternary"
    is_assign: bool = False

    @model_validator(mode="after")
    def _validate_forms(self):
        if not self.lit and not self.tokens:
            raise ValueError("operator must define either 'lit' or 'tokens'")
        if self.lit and self.tokens:
            raise ValueError("operator must not define both 'lit' and 'tokens'")
        if self.tokens and self.arity is None:
            self.arity = len(self.tokens)  # e.g., ternary ?: has 2 tokens, arity might be 3
        if self.arity is None:
            self.arity = 1 if self.fixity in ("prefix", "postfix") else 2
        return self

class TokensRoot(BaseModel):
    keywords: Dict[str, Dict[str, str]] = {}
    identifiers: Dict[str, Optional[str]] = {}
    literals: Dict[str, Optional[str]] = {}
    punct: Dict[str, Dict[str, str]] = {}
    operators: Dict[str, OperatorSpec] = {}

class Config(BaseModel):
    starting_token_value: int = Field(..., ge=0)
    conventions: Optional[Conventions] = None
    tokens: TokensRoot

# ----------------------- Normalization helpers ------------------------------

class FlatToken(BaseModel):
    name: str                      # e.g., IF, PLUS, IDENTIFIER
    lexeme: Optional[str] = None   # string this token matches (if any)
    categories: List[str] = []     # e.g., ["keyword","control_flow"]
    is_operator: bool = False
    precedence: Optional[int] = None
    assoc: Optional[str] = None         # "left" | "right" | "none"
    fixity: Optional[str] = None        # "prefix" | "postfix" | "infix" | "ternary"
    arity: Optional[int] = None
    is_assign: bool = False
    value: Optional[int] = None    # enum numeric value assigned later

def _append_token(tokens: Dict[str, FlatToken], ft: FlatToken):
    if ft.name in tokens:
        raise ValueError(f"Duplicate token name '{ft.name}'")
    tokens[ft.name] = ft

def normalize(cfg: Config) -> Dict[str, Any]:
    tks: Dict[str, FlatToken] = {}

    # 1) Keywords (flatten groups)
    kw_map: Dict[str, str] = {}
    for group_name, group in cfg.tokens.keywords.items():
        for name, lex in group.items():
            _append_token(tks, FlatToken(
                name=name, lexeme=lex,
                categories=["keyword", group_name]
            ))
            kw_map[lex] = name

    # 2) Identifiers
    for name, _ in cfg.tokens.identifiers.items():
        _append_token(tks, FlatToken(name=name, categories=["identifier"]))

    # 3) Literals
    for name, _ in cfg.tokens.literals.items():
        _append_token(tks, FlatToken(name=name, categories=["literal"]))

    # 4) Punctuation (delimiters/separators/misc)
    punct_pairs: List[Tuple[str, str]] = []
    punct_map: Dict[str, str] = {}
    punct_section = cfg.tokens.punct or {}

    for subgroup_name in ("delimiters", "separators", "misc"):
        subgroup = punct_section.get(subgroup_name, {})
        for name, lex in subgroup.items():
            _append_token(tks, FlatToken(
                name=name, lexeme=lex,
                categories=["punct", subgroup_name]
            ))
            if lex:
                punct_map[lex] = name

    # Pairs for matching (e.g., LPAR: RPAR)
    pairs_dict = punct_section.get("pairs", {})
    for left, right in pairs_dict.items():
        punct_pairs.append((left, right))

    # 5) Operators
    operators_lexemes: List[Tuple[str, str]] = []  # [(lexeme, NAME)]
    for name, spec in cfg.tokens.operators.items():
        if spec.lit is not None:
            _append_token(tks, FlatToken(
                name=name,
                lexeme=spec.lit,
                categories=["operator"],
                is_operator=True,
                precedence=spec.precedence,
                assoc=spec.assoc,
                fixity=spec.fixity,
                arity=spec.arity,
                is_assign=spec.is_assign,
            ))
            operators_lexemes.append((spec.lit, name))
        else:
            # multi-token operator (e.g., ternary ?:)
            _append_token(tks, FlatToken(
                name=name,
                lexeme=None,
                categories=["operator"],
                is_operator=True,
                precedence=spec.precedence,
                assoc=spec.assoc,
                fixity=spec.fixity,
                arity=spec.arity,
                is_assign=spec.is_assign,
            ))

    # 6) Assign enum values in a stable order you like
    # Order: keywords(control_flow,declarations,type_kw,misc_flow) -> punct(delim,sep,misc)
    #        -> operators(name order) -> identifiers/literals -> END
    order: List[str] = []

    def add_group(path: List[str]):
        # path like ["keyword","control_flow"]
        for n, ft in tks.items():
            if all(p in ft.categories for p in path):
                if n not in order:
                    order.append(n)

    # Keywords (preserve your original subgroups if present)
    for subgroup in cfg.tokens.keywords.keys():
        add_group(["keyword", subgroup])

    # Punct
    for subgroup in ("delimiters", "separators", "misc"):
        add_group(["punct", subgroup])

    # Operators
    for name, ft in tks.items():
        if ft.is_operator and name not in order:
            order.append(name)

    # Identifiers and Literals
    for cat in ("identifier", "literal"):
        for n, ft in tks.items():
            if cat in ft.categories and n not in order:
                order.append(n)

    # Assign values
    enum_list: List[Dict[str, Any]] = []
    value = cfg.starting_token_value
    for name in order:
        tks[name].value = value
        enum_list.append({"name": name, "value": value})
        value += 1
    # Add TOK_END
    enum_list.append({"name": "END", "value": value})

    # 7) Mark valued tokens (pass semantic values in Bison)
    valued_tokens: Set[str] = set()
    for n, ft in tks.items():
        if "identifier" in ft.categories or "literal" in ft.categories:
            valued_tokens.add(n)
    # Optional: treat builtin types as valued tokens if you want to carry a TypeNode
    # for n, ft in tks.items():
    #     if ft.categories == ["keyword","type_kw"]:
    #         valued_tokens.add(n)

    # 8) Longest-first operator lexemes for lexer
    op_lex_sorted = sorted(
        [lx for lx in operators_lexemes if lx[0]],
        key=lambda kv: len(kv[0]),
        reverse=True
    )

    # 9) Expose a compact serializable view for templates
    flat_tokens = [{
        "name": n,
        "lexeme": ft.lexeme,
        "categories": ft.categories,
        "is_operator": ft.is_operator,
        "precedence": ft.precedence,
        "assoc": ft.assoc,
        "fixity": ft.fixity,
        "arity": ft.arity,
        "is_assign": ft.is_assign,
        "value": ft.value
    } for n, ft in tks.items() if ft.value is not None]

    return {
        # enum / numbering
        "enum_list": enum_list,                    # [{name,value}, ... , {END,value}]
        # tokens, traits & groups
        "tokens_flat": flat_tokens,                # list of dicts per token
        "keywords_map": kw_map,                    # "if" -> "IF"
        "punct_pairs": punct_pairs,                # [(LPAR,RPAR), ...]
        "operators_lex_sorted": op_lex_sorted,     # [("==","EQUAL"), ("=","ASSIGN"), ...]
        "valued_tokens": sorted(valued_tokens),    # ["IDENTIFIER","INT_LITERAL",...]
        # convenience copies
        "starting_token_value": cfg.starting_token_value,
    }

# ----------------------------- CLI ------------------------------------------

@click.command()
@click.argument("config", type=click.Path(exists=True))
@click.option("-t", "--template-dir",
              default="templates",
              type=click.Path(exists=True, file_okay=False),
              help="Directory containing Jinja2 templates.")
@click.option("-o", "--out-dir",
              default="generated",
              type=click.Path(file_okay=False),
              help="Where to write the generated files.")
def main(config, template_dir, out_dir):
    with open(config, "r", encoding="utf-8") as f:
        data = yaml.safe_load(f)

    try:
        cfg = Config.model_validate(data)
    except Exception as e:
        click.echo(f"❌ Config error: {e}", err=True)
        sys.exit(1)

    env = Environment(
        loader=FileSystemLoader(template_dir),
        autoescape=False,
        trim_blocks=True,
        lstrip_blocks=True,
    )

    mapping = {
        "token.hpp.jinja2":      "token.hpp",
        "lexer_rules.l.jinja2":  "lexer/lexer_rules.l",
        "parser_rules.y.jinja2": "parser/parser_rules.y",
    }

    out_path = Path(out_dir)
    out_path.mkdir(parents=True, exist_ok=True)

    ctx = normalize(cfg)
    # Back-compat/raw tree for templates that expect `tokens.*`
    ctx["tokens"] = cfg.tokens.model_dump()
    ctx["conventions"] = cfg.conventions.model_dump() if cfg.conventions else {}
    ctx["starting_token_value"] = cfg.starting_token_value

    for tpl, out_file in mapping.items():
        rendered = env.get_template(tpl).render(**ctx)
        dest = out_path / out_file
        dest.write_text(rendered, encoding="utf-8")
        click.echo(f"✔ Wrote {dest}")


if __name__ == "__main__":
    main()
