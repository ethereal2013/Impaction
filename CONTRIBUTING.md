# Contributing to Impaction

First off, thank you for considering contributing to Impaction. This is a long-term, learning-oriented game engine project, and contributions of all sizes — code, documentation, bug reports, or design discussion — are genuinely welcome.

This document explains how the project is built, how to set up your environment, and what's expected of a pull request.

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [Ways to Contribute](#ways-to-contribute)
- [Getting Set Up](#getting-set-up)
- [Build System: Premake vs. CMake](#build-system-premake-vs-cmake)
- [Project Structure](#project-structure)
- [Coding Guidelines](#coding-guidelines)
- [Commit & Branch Conventions](#commit--branch-conventions)
- [Pull Request Process](#pull-request-process)
- [Reporting Bugs](#reporting-bugs)
- [Proposing Features / Design Changes](#proposing-features--design-changes)

## Code of Conduct

Be respectful, be constructive, and assume good faith. Impaction is an educational project as much as an engineering one — questions and beginner-friendly contributions are welcome alongside more advanced ones. Harassment, discrimination, or hostile conduct of any kind will not be tolerated.

## Ways to Contribute

You don't need to write engine code to contribute. Useful contributions include:

- **Bug reports** — reproducible issues, crashes, or incorrect rendering behavior.
- **Bug fixes** — small, focused patches are easiest to review and merge.
- **New engine features** — renderer improvements, new subsystems, tooling, etc. Larger features should be discussed in an issue first (see [Proposing Features](#proposing-features--design-changes)).
- **Documentation** — improving setup instructions, code comments, or architecture notes.
- **Build system maintenance** — keeping the Premake and CMake configs correct and in sync.
- **Platform support** — help extending or hardening Windows/Linux support, or scoping what it would take to support additional platforms.

## Getting Set Up

### 1. Fork and clone

Impaction uses git submodules for its dependencies, so clone recursively:

```bash
git clone --recursive https://github.com/<your-fork>/Impaction.git
```

If you already have a non-recursive clone:

```bash
git submodule update --init --recursive
```

### 2. Pick a build path

Impaction supports **two build systems**, each aimed at a different editor workflow — see the next section for details and which one you should use.

### 3. Build and run the Sandbox

The `Sandbox` project exists specifically for exercising engine features during development. Get it building and running before making changes, so you have a known-good baseline.

## Build System: Premake vs. CMake

This is a common point of confusion for new contributors, so it's worth being explicit.

Impaction maintains **two parallel build configurations**:

| File | Build system | Intended for |
|---|---|---|
| `premake5.lua` | [Premake5](https://premake.github.io/) | **Visual Studio** on Windows |
| `CMakeLists.txt` | [CMake](https://cmake.org/) | **CLion**, other CMake-aware editors, and CI / command-line builds |

**Rationale:** Premake's project generation produces a native, well-integrated experience specifically for Visual Studio, which is why it's kept for that workflow. CLion (and most other tooling, including most CI systems) is CMake-native, so CMake is used everywhere else. Rather than forcing a single generator to serve both IDEs equally poorly, each has its own first-class path.

**What this means for you as a contributor:**

- If you work in **Visual Studio**, generate the solution via Premake and build/test through that project.
- If you work in **CLion** (or another CMake-based setup), configure and build directly via `CMakeLists.txt`.
- If your change touches **source file lists, include paths, preprocessor definitions, or new dependencies**, update **both** `premake5.lua` and `CMakeLists.txt`. A change that only works under one build system is not considered complete.
- If you're unsure how to mirror a change across both files, say so explicitly in your pull request — a maintainer can help finish the other side rather than have the PR merge with one build system silently broken.
- Bug reports and issues about build failures should state **which build system** (Premake/Visual Studio or CMake/CLion) and **which platform** (Windows/Linux) you hit the issue on.

### Regenerating after a Premake change

If you edit `premake5.lua`, re-run the appropriate generation script (see [`scripts/`](scripts)) or `premake5 vs2022` (or your target action), then reload the solution in Visual Studio before compiling.

### Regenerating after a CMake change

Re-run the configure step:

```bash
cmake -S . -B build
cmake --build build
```

CLion will typically pick up `CMakeLists.txt` changes automatically and prompt a re-sync.

## Project Structure

```
Impaction/
├── Impaction/            # Engine source (core, rendering, etc.)
├── Sandbox/               # Example / playground application using the engine
├── Resources/Branding/    # Logo and branding assets
├── scripts/                # Project generation / setup scripts
├── CMakeLists.txt          # CMake build configuration (CLion / cross-platform)
├── premake5.lua             # Premake build configuration (Visual Studio)
└── .gitmodules               # Third-party dependencies
```

When adding new source files, place them under the relevant module in `Impaction/`, and make sure they're picked up by **both** build configurations (see above).

## Coding Guidelines

Impaction's initial architecture closely follows Hazel2D, and the current code style largely reflects that lineage. Until a formal style guide exists in this repository, contributors should:

- Match the surrounding code's naming, formatting, and structural conventions rather than introducing a new style within an existing file.
- Prefer clarity and consistency over cleverness — this is an educational codebase as much as a functional one.
- Target the project's stated dialect, **C++20**, and avoid compiler-specific extensions unless the platform code path explicitly requires them.
- Keep platform-specific code isolated and clearly guarded (e.g. behind existing platform macros), consistent with how `Core.h` / `EntryPoint.h` already separate Windows and Linux behavior.
- Avoid introducing new third-party dependencies without discussing them in an issue first — submodule additions affect both build systems and all contributors' clone sizes.

If/when a formal style guide (e.g. `.clang-format`) is added to the repository, it supersedes the guidance above.

## Commit & Branch Conventions

- Use short, descriptive branch names, e.g. `fix/sandbox-crash-on-resize` or `feature/renderer-batching`.
- Write commit messages that explain *what* changed and, where it isn't obvious, *why*.
- Keep commits focused — avoid bundling unrelated changes (e.g. a bug fix and a formatting pass) into a single commit.
- Rebase or squash noisy work-in-progress commits before opening a pull request where practical.

## Pull Request Process

1. **Open an issue first** for anything beyond a small fix — see [Proposing Features](#proposing-features--design-changes).
2. **Branch from `main`** and keep your branch reasonably up to date with it.
3. **Build and test with both build systems** if your change touches source lists, includes, or dependencies. At minimum, confirm it builds under the system matching your platform; note in the PR description if you were unable to verify the other.
4. **Describe the change**: what it does, why it's needed, and how you tested it (including platform: Windows/Linux, and build system: Premake/CMake).
5. **Keep the PR scoped** — a focused PR is easier and faster to review than a large, mixed one.
6. Expect review feedback — this is a young project with an evolving architecture, so some back-and-forth on design is normal even for reasonable changes.

## Reporting Bugs

When filing an issue, please include:

- **Platform:** Windows or Linux (and version/distro where relevant)
- **Build system:** Premake/Visual Studio or CMake/CLion
- **Steps to reproduce**
- **Expected vs. actual behavior**
- **Relevant logs, stack traces, or screenshots** (especially for rendering issues)

## Proposing Features / Design Changes

Because Impaction is still establishing its independent architecture (see the README's [Acknowledgements](README.md#inspiration-and-acknowledgements) section), non-trivial features or architectural changes should start as an issue or discussion before implementation:

- Describe the problem or gap you're addressing.
- Outline the proposed approach, especially if it diverges from the current Hazel2D-derived structure.
- Note any impact on the build system, submodules, or supported platforms.

This helps avoid duplicated effort and keeps larger design decisions visible to the rest of the project.

---

Thanks again for contributing — whether it's a one-line fix or a new subsystem, it helps move Impaction forward.
