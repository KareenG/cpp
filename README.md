# C++ Projects (Portfolio)

This repository contains C++ modules and mini-projects that focus on core software topics: concurrency, emulation/VM concepts, networking, and basic design patterns (C++17).

## Folders
- `mt/` – multithreading utilities (thread pool, thread-safe queues, periodic executor)
- `net/` – networking utilities
  - `net/tcp/` – TCP client/server helpers
  - `net/udp/` – UDP client/server helpers
- `lc3/` – LC-3 simulator modules (CPU, decoder, memory, traps, console I/O)
- `bf/` – VM/compiler-style components (program/memory/operations)
- `dp/` – utilities (object pool + helpers)
- `img_proc/` – image processing module (image types + processing helpers)

## How to run
Most projects are executed from the `tests/` folder:
1. Go to `tests/`
2. Enter the relevant project’s test folder
3. Run `check` (or `recheck`) from the terminal

## Arkanoid project
The Arkanoid-style game is in the `arkanoid` branch:
1. Switch to the branch: `git checkout arkanoid`
2. Follow the run instructions inside that branch (README / tests)
Reference game: [Arkanoid](https://www.classicgame.com/game/Arkanoid)
