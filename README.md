# sterm - a minimalistic terminal emulator based on the VTE library

## Requirements

* glib2
* GTK+ 3.0
* VTE 2.91
* cmake >= 2.8.8

## Installation

```
mkdir build
cd build
cmake [OPTIONS] ..
make
make install (as root)
```

### Available CMake options:

* **-DWITH_TESTS={ON,OFF}**
  Build the included (very basic) tests. To execute them run the `ctest` command
  after the build.

### Usage

Just run `sterm` after the build to start the terminal. `sterm --help` will give
you an overview of the basic options.
The main configuration file should be placed at `${HOME}/.config/sterm/sterm.ini`.

## Copyright

Copyright (c) 2016 by Jakob Nixdorf <flocke@shadowice.org>

