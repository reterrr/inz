# File: generate_lexer_defs.py
"""
This script reads a simple YAML/JSON configuration of tokens (keywords and operators)
and generates two files:
  - token.hpp: enum class Token and token-to-integer definitions
  - lexer_rules.l: Flex rules for keywords, operators, and identifiers/numbers.

Usage:
  python generate_lexer_defs.py config.yaml

The config file should have the structure:

keywords:
  IF: "if"
  ELSE: "else"
  WHILE: "while"

operators:
  PLUS: "+"
  MINUS: "-"
  EQUAL: "=="
  ASSIGN: "="

You can add groups as needed.
"""
import sys
import yaml  # pip install pyyaml
from jinja2 import Environment, FileSystemLoader

def main(config_path):
    with open(config_path) as f:
        cfg = yaml.safe_load(f)

    env = Environment(loader=FileSystemLoader(searchpath='.'),
                      trim_blocks=True, lstrip_blocks=True)
    template = env.get_template('lexer_defs.jinja2')

    output = template.render(
        keywords=cfg.get('keywords', {}),
        operators=cfg.get('operators', {}),
        delimiters=cfg.get('delimiters', {}),
        starting_token_value=cfg.get('starting_token_value', 100)
    )

    # Write token.hpp and lexer_rules.l
    with open('generated/token.hpp', 'w') as tokf:
        # token.hpp is included at the top of output until '%%LEXER_RULES%%'
        tokf.write(output.split('%%LEXER_RULES%%')[0])

    with open('lexer_rules.l', 'w') as lexf:
        # Everything after '%%LEXER_RULES%%'
        lexf.write(output.split('%%LEXER_RULES%%')[1])

    print("Generated token.hpp and lexer_rules.l")

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: python generate_lexer_defs.py config.yaml")
        sys.exit(1)
    main(sys.argv[1])