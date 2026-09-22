# Experiment 3 — Dirty-Code Analysis and Standards-Compliant Refactoring

This folder contains everything for the experiment:

```
Experiment-3/
├── original/
│   └── dirty_code.c        # BEFORE: deliberately dirty code
├── refactored/
│   └── clean_code.c        # AFTER: standards-compliant refactor
├── cppcheck_before.txt     # cppcheck console output on dirty_code.c
├── cppcheck_after.txt      # cppcheck console output on clean_code.c
├── Experiment3_Lab_Report.pdf
└── README.md
```

## 1. Why you must run cppcheck yourself

`cppcheck_before.txt` and `cppcheck_after.txt` currently contain **placeholder
text**, not real tool output — the sandbox that generated these files has no
internet/package access, so cppcheck could not be installed or run here.
You need to run it yourself (2 minutes) and paste the real output in, then
rebuild the PDF (or just replace the two .txt sections manually before
printing/exporting) so your report shows genuine results.

### Install cppcheck
- **Ubuntu/Debian/WSL:** `sudo apt-get update && sudo apt-get install -y cppcheck`
- **macOS (Homebrew):** `brew install cppcheck`
- **Windows:** download the installer from https://cppcheck.sourceforge.io

### Run it
From inside the `Experiment-3` folder:
```bash
cppcheck --enable=all --inconclusive --std=c11 original/dirty_code.c   > cppcheck_before.txt 2>&1
cppcheck --enable=all --inconclusive --std=c11 refactored/clean_code.c > cppcheck_after.txt  2>&1
```
Open both `.txt` files and confirm the warning classes listed in Section 6.3
of the PDF (unsafe strcpy/gets/sprintf, unchecked return values, dead code,
unused variable) appear in `cppcheck_before.txt` and are **absent** from
`cppcheck_after.txt`.

### (Optional) Regenerate the PDF with the real output
If you have Python available:
```bash
pip install reportlab
python3 build_report.py
```
This reads the two `.txt` files and `original/dirty_code.c` /
`refactored/clean_code.c` and rebuilds `Experiment3_Lab_Report.pdf` with
whatever is currently in those files — so do this *after* you've replaced
the placeholder text with your real cppcheck output.
If you'd rather not touch Python, just open the PDF, or write the report in
Word, and paste the real console output into the cppcheck section by hand.

## 2. Compiling / running the two programs (optional, to see behaviour)
```bash
gcc -Wall -Wextra -o dirty  original/dirty_code.c   -w   # -w hides its own warnings for demo
gcc -Wall -Wextra -o clean  refactored/clean_code.c       # should compile with ZERO warnings
./clean
```

## 3. Pushing everything to your GitHub repo

Your repo: `https://github.com/2301730207Sudhanshu/Experiment-3`

### If the repo is empty (first push)
```bash
git clone https://github.com/2301730207Sudhanshu/Experiment-3.git
cd Experiment-3
# copy in: original/, refactored/, cppcheck_before.txt, cppcheck_after.txt,
#          Experiment3_Lab_Report.pdf, build_report.py, README.md
git add .
git commit -m "Exp 3: dirty code analysis, refactor, cppcheck results, lab report"
git branch -M main
git push -u origin main
```

### If you already have the repo cloned locally
```bash
cd path/to/Experiment-3
# copy/overwrite the files listed above into this folder
git add .
git commit -m "Exp 3: dirty code analysis, refactor, cppcheck results, lab report"
git push
```

### If you get an authentication error on push
GitHub no longer accepts your account password for `git push`. Use a
Personal Access Token instead:
1. GitHub → Settings → Developer settings → Personal access tokens →
   Tokens (classic) → Generate new token → tick the `repo` scope.
2. When `git push` prompts for a password, paste the token instead of your
   GitHub password.

Alternatively, use GitHub Desktop or the "Upload files" button on the
repository's GitHub web page and drag-and-drop the same files.

## 4. Submitting
Upload `Experiment3_Lab_Report.pdf` wherever your faculty wants the report,
and make sure the GitHub link in the report / your submission points to
`https://github.com/2301730207Sudhanshu/Experiment-3` with both
`original/dirty_code.c` and `refactored/clean_code.c` visible in the repo.
