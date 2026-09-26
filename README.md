<div align="center">

<img src="Resources/Branding/logo.png" alt="Impaction Engine Logo" width="200"/>

# Impaction

**A C++20 2D Game Engine built for learning, experimentation, and long-term graphics programming development.**

[![License: Apache-2.0](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-lightgrey)](#requirements)
[![Language](https://img.shields.io/badge/language-C%2B%2B20-00599C)](#requirements)
[![Graphics API](https://img.shields.io/badge/graphics-OpenGL-5586A4)](#requirements)
[![Status](https://img.shields.io/badge/status-early%20development-orange)](#current-project-status)

[Getting Started](#getting-started) •
[Build System](#build-system) •
[Project Structure](#project-structure) •
[Contributing](#contributing) •
[Acknowledgements](#inspiration-and-acknowledgements)

</div>

---

## What is Impaction?

Impaction is a 2D game engine written in modern C++ that can be used to build 2D games or any other custom 2D application requiring rendering mechanics. The project is developed openly as both a working engine and a long-term learning ground for engine architecture, rendering, and tooling.

## Current Project Status

| | |
|---|---|
| **Development stage** | Early — core fundamentals are set up and working |
| **Graphics API** | OpenGL |
| **Language / Dialect** | C++20 (ISO/IEC 14882:2020) |
| **Supported platforms** | Windows, Linux |
| **License** | [Apache-2.0](LICENSE) |

Impaction is under active, incremental development. Interfaces, subsystems, and project layout may change without notice while the engine matures.

## Features

> This section tracks engine capabilities as they land. Contributions that add or extend a feature area are expected to keep this list current.

- Core application / entry-point layer
- OpenGL-based 2D rendering pipeline
- Cross-platform build support (Windows & Linux)
- Sandbox project for iterating on engine features in isolation

## Requirements

- **Compiler:** A C++20-capable compiler (MSVC on Windows, GCC/Clang on Linux)
- **Git:** with submodule support
- **IDE (recommended):**
  - [Visual Studio](https://visualstudio.microsoft.com/) — via the Premake build
  - [CLion](https://www.jetbrains.com/clion/) — via the CMake build
- **Graphics driver:** with OpenGL support

> Only Windows and Linux are supported. Other editors/IDEs and operating systems will likely require manual setup — see [`CMakeLists.txt`](CMakeLists.txt), [`premake5.lua`](premake5.lua), [`EntryPoint.h`](Impaction/src/Impaction/Core/EntryPoint.h), and [`Core.h`](Impaction/src/Impaction/Core/Core.h) as the starting points for porting.

## Getting Started

### 1. Clone the repository

Impaction pulls in dependencies as git submodules, so clone recursively:

```bash
git clone --recursive https://github.com/ethereal2013/Impaction.git
```

If you already cloned without `--recursive`, fetch the submodules with:

```bash
git submodule update --init --recursive
```

### 2. Generate the project

See [Build System](#build-system) below to pick the right path for your toolchain, then open the generated project in Visual Studio or CLion and build the `Sandbox` (or your own) target.

## Build System

Impaction intentionally supports **two build systems**, targeted at two different workflows:

| Build system | Target IDE / workflow | Config file |
|---|---|---|
| **Premake5** | Visual Studio on Windows | [`premake5.lua`](premake5.lua) |
| **CMake** | CLion, and any other CMake-aware editor or command-line workflow | [`CMakeLists.txt`](CMakeLists.txt) |

**Why two build systems?** Premake's Visual Studio project generation is a better fit for a native Visual Studio workflow, while CLion (and most other editors/CI) is CMake-first. Rather than forcing one toolchain to awkwardly support both IDEs, Impaction keeps a dedicated path for each:

- Use **Premake** if you're developing with Visual Studio.
- Use **CMake** if you're developing with CLion, another CMake-aware IDE, or the command line.

Both paths build from the same source tree — pick whichever matches your editor.

### Building with Premake (Visual Studio)

1. Run the appropriate generation script for your OS (see [`scripts/`](scripts)) or invoke `premake5` directly, e.g.:

   ```bash
   premake5 vs2022
   ```

2. Open the generated `.sln` in Visual Studio and build.
3. If you change `premake5.lua`, re-run the generation step and reload the solution before compiling.

### Building with CMake (CLion / command line)

```bash
cmake -S . -B build
cmake --build build
```

Or open the repository root directly in CLion — it will detect `CMakeLists.txt` and configure the project automatically.

> **Note:** If you edit the build configuration, keep both `premake5.lua` and `CMakeLists.txt` in sync where practical. Build-system-specific issues should be reported against the relevant file.

## Project Structure

```
Impaction/
├── Impaction/            # Engine source (core, rendering, etc.)
├── Sandbox/               # Example / playground application using the engine
├── Resources/Branding/    # Logo and branding assets
├── scripts/                # Project generation / setup scripts
├── CMakeLists.txt          # CMake build configuration (CLion / cross-platform)
├── premake5.lua             # Premake build configuration (Visual Studio)
├── .gitmodules              # Third-party dependencies
└── LICENSE
```

## Roadmap

Impaction began as a close architectural follow of Hazel2D (see [Acknowledgements](#inspiration-and-acknowledgements)) and is intended to evolve beyond that reference implementation over time, introducing independently designed systems, experiments, and features. There is no fixed timeline — track progress via [Issues](../../issues) and [Pull Requests](../../pulls).

## Contributing

Impaction is a long-term project, and contributions, suggestions, bug reports, and discussions are always welcome — whether you want to improve the engine, experiment with new systems, or simply explore the codebase.

See [CONTRIBUTING.md](CONTRIBUTING.md) for setup instructions, coding conventions, and the pull request process.

## Inspiration and Acknowledgements

Impaction is heavily inspired by **Hazel2D**, the game engine developed by [The Cherno](https://www.youtube.com/@TheCherno). Its initial architecture and implementation closely follow Hazel, as the project began primarily as a learning exercise and a first serious attempt at building a game engine.

At its current stage, the project still closely resembles Hazel's architecture and implementation — this is intentional, reflecting the project's educational origin rather than an attempt to present the initial implementation as independently designed. As development continues, Impaction is intended to diverge with independently designed systems, experiments, architectural changes, and new features.

## License

Impaction is licensed under the [Apache License 2.0](LICENSE).
