# Experiment 3 — Memory Defect Detection and Remediation with Valgrind and ASan

Three C memory defects, each as a buggy/fixed pair, analysed with **Valgrind Memcheck**
and **AddressSanitizer (ASan)**.

| # | Defect | Buggy | Fixed |
|---|--------|-------|-------|
| 1 | Uninitialised variable read | `src/1_uninit_buggy.c` | `src/1_uninit_fixed.c` |
| 2 | Memory leak | `src/2_leak_buggy.c` | `src/2_leak_fixed.c` |
| 3 | Double free | `src/3_doublefree_buggy.c` | `src/3_doublefree_fixed.c` |

## Build

```bash
# Valgrind build (plain debug symbols, no instrumentation)
gcc -g -O0 -o bin/<name>_vg src/<name>.c

# AddressSanitizer build
gcc -g -O0 -fsanitize=address -o bin/<name>_asan src/<name>.c
```

## Run

```bash
# Valgrind Memcheck
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/<name>_vg

# AddressSanitizer (just run the binary — instrumentation is baked in)
./bin/<name>_asan
```

## Logs

Full captured output for every binary is in `logs/`:
- `logs/valgrind_all.txt` — Memcheck output for all six binaries
- `logs/asan_all.txt` — ASan/LeakSanitizer output for all six binaries

## Report

The full lab report (aim, code listings, before/after diagnostics, interpretation,
and result) is at `report/Lab_Report_Exp3_Memory_Defects.pdf`.

## Summary of results

| Defect | Valgrind (Before → After) | ASan (Before → After) |
|---|---|---|
| 1. Uninitialised read | 1 error → 0 errors | Not detected → N/A (by design — see report) |
| 2. Memory leak | 2000 B / 5 blocks lost → 0 lost | Leak detected → No leak |
| 3. Double free | 1 invalid free() → 0 errors | Aborted (double-free) → Clean exit |
