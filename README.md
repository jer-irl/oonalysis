# oonalysis
[![Build Status](https://travis-ci.org/jeresch/oonalysis.svg?branch=master)](https://travis-ci.org/jeresch/oonalysis)

## Overview
```
[FILE] ---> [SQLITE] ---> [VIS]
      parse         display
```
Core contains parsing material.
Db is the interface to the sqlite backend.
Gui contains the Qt files.
I'd like to move to QtQuick.

## Building
To build:
```
git submodule init
cmake .
make
```

## Contributors
Please make a new branch for every large new feature, and open a pull request to get it merged in.
