# remoteexecutor

Simple framework for issuing work to a set of workers.

## Compilation

These instructions assume that the project has been cloned into directory named `remoteexecutor`.

### Compilation in the source directory

    cd remoteexecutor
    ./autogen.sh
    ./configure
    make

### Compilation outside the source directory

    cd remoteexecutor
    ./autogen.sh
    cd ..
    mkdir workdir
    cd workdir
    ../remoteexecutor/configure
    make

## Installation

By default the shared library is installed to `/usr/local/lib` and headers into to
`/usr/local/include`. If this is not desired, then provide different path when running `configure`,
for example:

    ./configure --prefix=$HOME

Note that `configure` command allows plethora of additional options. For more
info:

    ./configure --help

After configuration has been done, run:

    make install
