# WELCOME TO THE KNOCK 'EM ALL REPO!

## INTRODUCTION:
**What is this repository all about?**  
This repository is an implementation of the ten pin bowling game.
It provides a bowling class inside which the recording of the game history and the business logic is performed.

A typical ten pin game will contain 1 instance of a game class for each player.
Within that class, will be 10 instances of the frame class and each frame
instance will consist of atleast 2 ball class instances.
For information on the rules of the game, see <http://slocums.homestead.com/gamescore.html>

There is now a more improved version of this repo (i.e. code that is done in a completely different style).
You can check this out by searching for 'clean_em_all' repo.

### Generic Build Instructions

#### Setup

To build this project, you need to tell your build system where to find the headers
and source files not only for this project but also the Google Test framework.
The exact way to do it depends on which build system you use, and is usually straightforward.

#### Build

Simply run `make` in the root directory. Note that the compiler needs to be g++.
For more information on how to use other compilers see <https://github.com/google/googletest/tree/master/googletest>

### Building Google Test Framework

Suppose you put Google Test in directory `${GTEST_DIR}`. To build it, create a
library build target (or a project as called by Visual Studio and Xcode) to
compile

    ${GTEST_DIR}/src/gtest-all.cc

with `${GTEST_DIR}/include` in the system header search path and `${GTEST_DIR}`
in the normal header search path. Assuming a Linux-like system and gcc,
something like the following will do:

    g++ -isystem ${GTEST_DIR}/include -I${GTEST_DIR} \
        -pthread -c ${GTEST_DIR}/src/gtest-all.cc
    ar -rv libgtest.a gtest-all.o

(We need `-pthread` as Google Test uses threads.)

Next, you should compile your test source file with `${GTEST_DIR}/include` in
the system header search path, and link it with gtest and any other necessary
libraries:

    g++ -isystem ${GTEST_DIR}/include -pthread path/to/your_test.cc libgtest.a \
        -o your_test

As an example, the make/ directory contains a Makefile that you can use to build
Google Test on systems where GNU make is available (e.g. Linux, Mac OS X, and
Cygwin). It doesn't try to build Google Test's own tests. Instead, it just
builds the Google Test library and a sample test. You can use it as a starting
point for your own build script.

If the default settings are correct for your environment, the following commands
should succeed:

    cd ${GTEST_DIR}/make
    make
    ./sample1_unittest

If you see errors, try to tweak the contents of `make/Makefile` to make them go
away. There are instructions in `make/Makefile` on how to do it.
