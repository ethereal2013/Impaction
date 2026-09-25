# Impaction

<p align="center">
  <img src="Resources/Branding/logo.png" width="412">
</p>

A C++ 2D Game Engine inspired from Hazel 2D built for learning, experimentation and long-term graphics programming development.

## Current Project Status

**Development:** Impaction is currently in its first half with the fundamentals of the engine set up and working.

**Graphics API:** OpenGL.

**Language:** C++.

**Dialect:** C++ 20 (ISO/IEC 14882:2020).

**Platform:** Windows and Linux Supported.

**License:** [License](LICENSE)

## What is Impaction?

Impaction is a 2D Game Engine that can be used to create 2D games or any other custom 2D application that require rendering mechanics.

## Getting Started

### Requirements

*Note: Currently, only Windows and Linux are supported*

To build a 2D game or software using Impaction, using [Visual Studio](https://visualstudio.microsoft.com/) or [CLion](https://www.jetbrains.com/clion/) is highly recommended.
Setup on other Code Editors or IDEs may require significant manual setup and configuration.

The [CMake](CMakeLists.txt), [EntryPoint.h](Impaction/src/Impaction/Core/EntryPoint.h) and [Core.h](Impaction/src/Impaction/Core/Core.h) must be edited accordingly whilst experimenting usage with Operating Systems other than Windows or Linux.

### Cloning

**1. Downloading the Repository:**
Make sure git is installed. Open command prompt or git bash at the desired directory. If opened at home or root then `cd` into the desired directory. Finally clone the repository with

`git clone --recursive https://github.com/ethereal2013/Impaction.git`.

If the repository was previously cloned non-recursively(without ` --recursive`), use `git submodule update --init` to clone the necessary submodules.

**2. Regenerating the project:**
If changes are made, make sure to update and save the [premake](premake5.lua) as necessary and then run the project generation file in accordance to your Operating System to regenerate and reload the project before compilation.

## Inspiration and Acknowledgements

Impaction is heavily inspired by Hazel2D, the game engine developed by The Cherno. Its initial architecture and implementation closely follow Hazel as the project began primarily as a learning opportunity and as a first serious attempt at developing a game engine
At its current stage, the project closely resembles Hazel's architecture and implementation. This is intentional and shows the project's educational origin rather than an attempt to present the initial implementation as an independently designed game engine.
As development progresses, Impaction is intended to evolve beyond its initial reference implementation i.e. Hazel2D. Soon having independently designed systems, experiments, architectural changes, and features introduced over time.

## Contributing

Impaction is a long-term project, and contributions, suggestions, bug reports, and discussions are always welcome. Whether you are interested in improving the engine, experimenting with new systems, or simply exploring the codebase, you are welcome to participate.

As Impaction continues to develop, this repository will evolve alongside it. We hope that the project can serve not only as an engine, but also as a place to experiment, learn, and explore the foundations of game and graphics programming.
