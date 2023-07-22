# MathematicaCLI
Command Line Interface for Mathematica, a modern equation solver.

# Motivation
MathematicaCLI is the primitive form of Mathematica, a future software for learning and discovering math.
Mathematics is a world of beauty and its abstractness may be difficult for most people. Making math easy
is a problem for the century and this project is a way to address it.

# Platforms
MathematicaCLI is built for Windows, macOS and Linux. However, Windows and macOS are the only platforms I can test regularly,
Linux is only tested through [GitHub Actions](https://github.com/ZeXo-Softwares/MathematicaCLI/actions).

# Getting started
MathematicaCLI uses [premake5](https://premake.github.io) to build the source, and for now, a binary source of such program is distributed with the source code.
To get started you'd need to install python 3.x (I'm using 3.11) and launch the scripts.
To generate project files for your platform launch `generate.py` and to clean generated files use `clean.py`. You can also use the wrapper `run.py`
to access quickly the binaries, specifying the arguments and thee configuration. There is also a new script, `todo.py`. Its role is to generate a `todo.txt` file, containing information about todos and more, extracted directly from source files.

# Code conventions
I use `camelCase` for variables, `UPPER_SNAKE_CASE` for macros and `UpperCamelCase` for files, directories, functions, struct, classes and namespaces. Every function that would be defined in a global scope is instead declared in the `Mathematica` namespace. Every class, struct or type definition has the prefix `M`, enumerators start with `E`, and function pointers start with `F`. I use `STL` implementations for data structures, and these types are aliased by the `using` keyword. Every definition of these types can be found in `Build/Include/Utility/Types.h`. For member variables of classes, I generally use the prefix `m`, for instance: `mTree`. For structs, variables use plain camelCase. Last, to bind functionalities for `todo.py`, use the keywords: `TODO`, `TODO (late)`, `NOTE` and `REFACTOR`, each followed by a space and a colon. The following phrase will then be added in `todo.txt`.
**For contributions, please stick to these conventions. Any pull request will not be accepted if those requirements are not met.**

# Authors
The development of this project is entirely carried on by me, @Ciridev.

# Licensing
This project is licensed under the MIT license.
