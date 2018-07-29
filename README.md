# oonalysis
[![Build Status](https://travis-ci.org/jeresch/oonalysis.svg?branch=master)](https://travis-ci.org/jeresch/oonalysis)

## Introduction
This is a project I worked on mostly in the fall of 2017 (but the git
history was wiped in July of 2017, and there was work beforehand).  The
overall goal is to provide a way to explore the semantic and structural
content of code, in a way that is more suited to human comprehension
than reading plain source text.  My plans are pretty lofty for this
project, and despite a hiatus while I seek employment, I am planning to
return to it.

I taught myself C++ with this project, so some of the code is not up to
my current standards.  In the future I hope to modernize and rewrite
portions of the codebase, as a part of migrating to tools that are more
appropriate for the task.

## Current Status
The project currently targets C and C++ source code for analysis, and
has a functioning CLI and GUI, with limited visualization rendering.
There is GUI tooling for semantic "projects" to maintain state between
runs of the program.

## Technical Overview
I hope to target more source languages than C++ in the future, so I
built the core architecture to have swappable backends.  From a very
high level, first a backend engine parses input source code, serializes
the important relationships and details to a relational database, and
then this database is read by the frontend visualization engine.

```
[FILE] ---> [SQLITE] ---> [VIS]
      parse         display
```

The project is written in C++ primarily because it seems like the best
choice for cross-language calls if I need to write additional backend
engines in different languages.  Another benefit is that I got to teach
myself C++

The project is built with CMake, for eventual cross-platform targeting.
I've only tested building on MacOS though, so you may have trouble on
other platforms.  Library dependencies are hooked in by a mix of git
submodules (very handy and I have a lot of control over their source),
and system installs, installed through Homebrew for MacOS.

Currently, C++ and C are parsed using the C LibClang interface into the
awesome Clang library.  SQLite is used for storage, using the (again,
awesome) sqlite_orm by fnc12 for nice C++ access.  The CLI is written
using the Boost library Program_options.  The GUI is built with QT,
which I've also had fun learning and using.

I've been going back and forth on rendering.  I'm tempted to roll my own
rendering engine built directly on QT for native interactivity, but I
think it might be better to use a pre-made tool.  I've gotten graphviz
to work for some rendering tasks, but the output isn't interactive, and
the GPL license isn't something I'm comfortable going with right now.
The other option I'm considering is D3, using QT's embedded Chromium
engine.  The bridge between the javascript and C++ world will be
difficult to manage, but I have experience with D3 and it does a lot of
nice things, and can also be interactive.

## Source Code Overview
Library submodules live in lib/.  My source code is in src/.  src/core
contains all of the parsing engines, pretty much just src/core/clang for
now.  src/db contains the ORM definitions and datatypes for SQLite
serialization.  src/graph contains a graphing library I'm writing for
generic force-directed graph layouts and analysis.  src/gui contains the
QT code for display and project usage.  src/metrics contains analysis
routines to be run on a populated SQLite database.  src/util contains
general utilities.

## Building
I'm using CLion, but one should be able to build using plain CMake.

To build:
```
git submodule init
cmake .
make
```

## License
Right now, I'm leaving the software unlicensed.  You have my informal
permission to look at the source code and compile and use the program,
but I do not consent to my code being used in other projects.  This may
change in the future.
