# STerm - a minimalistic terminal emulator based on the VTE library

## Requirements

* [glib2](https://developer.gnome.org/glib/)
* [GTK+ 3](http://www.gtk.org/)
* [VTE 2.91](https://developer.gnome.org/vte/)
* [cmake](https://cmake.org/) >= 3.0.0

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

## Bugs

Please report any bugs and feature requests on [GitHub](https://github.com/flocke/sterm/issues).
Pull requests with fixes and improvements are always welcome.

## Contributors

* [Johannes Nixdorf](https://github.com/mixi)

## Rewrite

This is the rewrite of my first version of STerm, which can still be found in the
[old-and-broken](https://github.com/flocke/sterm/tree/old-and-broken) branch on GitHub. It has the
same dependencies and should be mostly feature compatible with the old version (including the
config file syntax and options). That's why a update to this new version should be possible without
any problems.

## Copyright

Copyright (c) 2016 by Jakob Nixdorf <flocke@shadowice.org>

