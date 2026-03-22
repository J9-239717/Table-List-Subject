# CS Degree Tracker — HUST

A personal CLI tool written in C that helps me track and manage
all courses in my Computer Science degree at HUST Hanoi.

I built this because I wanted a fast, local way to check my GPA,
plan which courses to take next, and understand what I still need
to graduate — without relying on the university's web portal.

## Features

| # | Feature | Description |
|---|---|---|
| 1 | Set up data | Input grades and scores for each course |
| 2 | Save data | Persist all data to a local `.txt` file |
| 3 | Print player | Display current student profile (debug view) |
| 4 | Check what to study this term | Show recommended courses for a given semester |
| 5 | Show table | Print a full formatted table of all courses |
| 6 | Count CPA | Calculate cumulative GPA from all graded courses |
| 7 | Show failed subjects by type | List courses not yet passed, grouped by subject type |
| 8 | Check graduation & remaining credits | Show how many credits remain to graduate |
| 9 | Check what to study (IT subjects only) | Same as #4 but filtered to IT-major courses only |
| 10 | Mismatch subjects | Detect inconsistencies between planned and actual course data |
| 11 | Grade predictor | Given a midterm score, calculate what final grade is achievable |

## Why I Built This

The university portal is slow and doesn't let me easily answer
questions like:
- "What is my current CPA?"
- "Which courses do I still need this term?"
- "If I scored X on the midterm, what grade can I still get?"

So I built a CLI tool in C that stores everything locally and
answers those questions instantly.

## Build & Run

**Linux / macOS:**
```bash
cd src
gcc main.c -o tracker
./tracker
```

**Windows:**
```bash
cd src
gcc main.c -o tracker.exe
tracker.exe
```

> Make sure to save data (option 2) before exiting,
> otherwise changes will be lost.

## Data

Course data is loaded from and saved to a local `.txt` file.
The dataset is based on the full CS curriculum at
Hanoi University of Science and Technology (HUST).

## What I Learned

- File I/O in C (reading and writing structured data to `.txt`)
- Building a menu-driven CLI application
- Implementing GPA calculation logic from scratch
- Structuring a medium-sized C project across multiple source files
