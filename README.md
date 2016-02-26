# STerm - a minimalistic terminal emulator based on the VTE library

## Requirements

* glib2
* GTK+ 3.0
* VTE 2.91
* cmake >= 3.0.0

## Installation

```
mkdir build
cd build
cmake [OPTIONS] ..
make
make install (as root)
```

### Available CMake options:

* **-DWITH_TOOLS={ON,OFF}** (default: ON)

  Build some helper tools (mostly to be used in keybindings).

* **-DWITH_TESTS={ON,OFF}** (default: OFF)

  Build the included (very basic) tests. To execute them run the `ctest` command after the build.
  This is still off by default since the included tests are very limited at the moment.

### Usage

Just run `sterm` after the build to start the terminal. `sterm --help` will give you an overview of
the basic options. The main configuration file should be placed at
`${XDG_CONFIG_HOME}/sterm/sterm.ini` (with `${XDG_CONFIG_HOME}` usually being `${HOME}/.config`).

## Rewrite

This is the rewrite of my first version of STerm, which can still be found in the `old-and-broken`
branch on GitHub. It has the same dependencies and should be mostly feature compatible with the old
version (including the config file syntax and options). That's why a update to this new version
should be possible without any problems.

## Copyright

Copyright (c) 2016 by Jakob Nixdorf <flocke@shadowice.org>

