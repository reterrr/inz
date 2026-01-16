#!/bin/bash
# Skrypt do uruchamiania showcase examples i zbierania wyników
# Użycie: ./scripts/run_showcases.sh [ścieżka_do_binarki_inz]

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
SHOWCASE_DIR="$PROJECT_ROOT/examples/showcase"
OUT_DIR="$SHOWCASE_DIR/_out"
INZ_BIN="${1:-$PROJECT_ROOT/build/inz}"

# Kolory
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo "=== Showcase Examples Runner ==="
echo "Binary: $INZ_BIN"
echo "Showcase dir: $SHOWCASE_DIR"
echo ""

# Sprawdź czy binarka istnieje
if [ ! -f "$INZ_BIN" ]; then
    echo -e "${RED}ERROR: Binary not found: $INZ_BIN${NC}"
    echo "Build the project first or provide path as argument"
    exit 1
fi

# Utwórz katalog wyjściowy
mkdir -p "$OUT_DIR"

# Funkcja uruchamiająca pojedynczy showcase
run_showcase() {
    local case_dir="$1"
    local case_name="$(basename "$case_dir")"
    local case_out="$OUT_DIR/$case_name"
    
    echo -e "${YELLOW}Running: $case_name${NC}"
    mkdir -p "$case_out"
    
    # Utwórz tymczasowy TOML dla tego case'a
    local tmp_toml="$case_out/temp_project.toml"
    cat > "$tmp_toml" << EOF
[files]
files_dir = "$case_dir"

[flags]

[link]
EOF
    
    # Uruchom z --dump-ast
    echo "  - Generating AST dump..."
    if timeout 30 "$INZ_BIN" "$tmp_toml" --dump-ast > "$case_out/ast.txt" 2>&1; then
        echo -e "    ${GREEN}OK${NC}"
    else
        echo -e "    ${RED}FAILED${NC}"
        mv "$case_out/ast.txt" "$case_out/ast_error.txt" 2>/dev/null || true
    fi
    
    # Uruchom z --dump-ir
    echo "  - Generating IR dump..."
    if timeout 30 "$INZ_BIN" "$tmp_toml" --dump-ir > "$case_out/ir.ll" 2>&1; then
        # Ogranicz do 250 linii jeśli za duży
        if [ "$(wc -l < "$case_out/ir.ll")" -gt 250 ]; then
            head -n 250 "$case_out/ir.ll" > "$case_out/ir_truncated.ll"
            echo "... [truncated, see full ir.ll]" >> "$case_out/ir_truncated.ll"
        fi
        echo -e "    ${GREEN}OK${NC}"
    else
        echo -e "    ${RED}FAILED${NC}"
        mv "$case_out/ir.ll" "$case_out/ir_error.txt" 2>/dev/null || true
    fi
    
    # Uruchom normalnie (bez dump)
    echo "  - Running program..."
    if timeout 30 "$INZ_BIN" "$tmp_toml" > "$case_out/run.txt" 2>&1; then
        echo -e "    ${GREEN}OK${NC}"
    else
        echo -e "    ${RED}FAILED (expected for negative cases)${NC}"
        mv "$case_out/run.txt" "$case_out/run_error.txt" 2>/dev/null || true
    fi
    
    # Cleanup
    rm -f "$tmp_toml"
    echo ""
}

# Iteruj po katalogach showcase (posortowane)
for case_dir in $(find "$SHOWCASE_DIR" -maxdepth 1 -type d -name "[0-9]*" | sort); do
    run_showcase "$case_dir"
done

echo "=== Done ==="
echo "Results saved to: $OUT_DIR"
