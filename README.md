# CodinGame Starter Project

This repository is a starter project to develop C++ CodinGame bots. You can read [this article on my blog](https://virtual-atom.com/codingame/tooling/) to learn how to use it.

## Contents

* `src/bot.cpp`, the main source file for the bot
* `src/configuration.h`, the main configuration file for the bot
* `tests/unit_tests.cpp`, the main unit tests file
* `merge_source_files.py`, a simple python script to merge source code into a single file
* `.vscode/` folder that activate C++ indexing and python linting in the project
* `CMakeLists.txt`, to generate a build configuration.

## Requirements

This project is meant to be used with the following tools installed:
* `cmake` to generate a build configuration for your projects
* `ninja` or `make` to build your projects (those are the only generators that produces `compile_commands.json` files, used by VSCode to parse and index C++ sources)
* `clang` to compile c++ files
* `python` to execute `merge_source_files`
* `lld` to link compiled c++ files.

If you want to use another compiler or another linker, add options for your configuration in the `CMakeLists.txt` file.

It is part of a set-up I use to develop C++ CodinGame bots. A [VSCode extension](https://github.com/tdelame/codingame_vscode_extension) feeds the following variables to the cmake file:
* `REPOSITORY_ROOT`, which is the path to my main repository, storing all my tools and my bots
* `INCLUDE_DIR`, path to the folder containing all the common headers I use for bots and tools
* `LIB_DIR`, path to the folder containing all the common libraries I use for my tools


