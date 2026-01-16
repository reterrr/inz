# Showcase Examples

Minimalny zestaw przykładów demonstrujących konstrukcje języka Kolka.

## Struktura

| Katalog | Konstrukcje | Pliki | Oczekiwany wynik |
|---------|-------------|-------|------------------|
| `01_minimal_package` | package, pub fn, return | `minimal.kl` | Kompiluje się, nic nie wypisuje |
| `02_imports` | import, alias (as), wywołanie przez ścieżkę | `main.kl`, `utils.kl` | Wypisuje: 20 |
| `03_structs` | struct, pub struct, inicjalizacja, dostęp do pól | `structs.kl` | Wypisuje: 10, 100 |
| `04_functions` | fn, argumenty, return, wywołania | `functions.kl` | Wypisuje: 42, 30, 80 |
| `05_control_flow` | if/else if/else, while, do-while, break, continue | `control.kl` | Seria liczb |
| `06_mutability_refs` | mut, &, &mut, *, deref store/load | `refs.kl` | Seria wartości |
| `07_arrays_box` | Box::<T>, box_new, box_get, box_set, box_len, literał tablicowy | `arrays.kl` | 0,10,20,30,40,5,true,2 |
| `08_types` | i32, i64, f32, f64, bool, char, operatory | `types.kl` | Seria wartości |
| `09_load_fn` | wbudowane funkcje runtime (print, box_*) | `loadfn.kl` | 42, 123 |
| `90_negative_cases` | Błędy semantyczne | 3 pliki | Błędy kompilacji |

## Uruchomienie

### Pojedynczy przykład
```bash
cd examples/showcase/01_minimal_package
../../../build/inz ../project.toml
```

### Wszystkie przykłady ze zbieraniem wyników
```bash
./scripts/run_showcases.sh ./build/inz
```

Wyniki zostaną zapisane w `examples/showcase/_out/`.

## Generowanie materiałów do pracy

Po uruchomieniu skryptu, w `_out/<nazwa>/` znajdziesz:
- `ast.txt` - zrzut AST (--dump-ast)
- `ir.ll` - wygenerowany LLVM IR (--dump-ir)
- `run.txt` - wynik uruchomienia

## Negative cases

Katalog `90_negative_cases/` zawiera przykłady celowo generujące błędy:
- `unresolved_import.kl` - import nieistniejącego modułu
- `unresolved_symbol.kl` - wywołanie nieistniejącej funkcji
- `wrong_arity.kl` - zła liczba argumentów
