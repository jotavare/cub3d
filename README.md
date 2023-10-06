- sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
- [https://www.youtube.com/watch?v=bYS93r6U0zg](https://www.youtube.com/watch?v=bYS93r6U0zg)
- [https://github.com/42Paris/minilibx-linux](https://github.com/42Paris/minilibx-linux)
- [x.org](https://www.x.org/wiki/)
- [https://www.x.org/releases/X11R7.6/doc/libX11/specs/libX11/libX11.html](https://www.x.org/releases/X11R7.6/doc/libX11/specs/libX11/libX11.html)
- https://www.youtube.com/watch?v=nKcfhI1B4mA
- cc main.c -Lminilibx-linux -lmlx_Linux -lX11 -lXext

```
gcc program.c -Lminilibx-linux -lmlx_Linux -o process -lX11 -lXext

Do make into the minilibx

minilibx-linux-> Path with the lib
mlx_Linux-> Name of the archive file (libmlx_Linux.a)
```

```
This is the MinilibX, a simple X-Window (X11R6) programming API in C, designed for students, suitable for X-beginners.

Contents

    source code in C to create the mlx library
    man pages (in man/ directory)
    a test program (in test/ directory) is built with the library
    a public include file mlx.h
    a tiny configure script to generate an appropriate Makefile.gen

Requirements for Linux

    MinilibX only support TrueColor visual type (8,15,16,24 or 32 bits depth)
    gcc
    make
    X11 include files (package xorg)
    XShm extension must be present (package libxext-dev)
    Utility functions from BSD systems - development files (package libbsd-dev)
    e.g. sudo apt-get install gcc make xorg libxext-dev libbsd-dev (Debian/Ubuntu)

Requirements for MacOS

    Xquartz

➜  ~ Brew install Xquartz
➜  ~ reboot
➜  ~ xeyes # run an hello world X11 app

MlX Color Opacity / Transparency / Alpha (32 bits depth)

    0xFF (fully transparent) or 0x00 (fully opaque)

Compile MinilibX

    run ./configure or make both will make a few tests, create Makefile.gen and then automatically run make on this generated Makefile.gen . libmlx.a and libmlx_$(HOSTTYPE).a are created. test/mlx-test binary is also created.

Install MinilibX

    no installation script is provided. You may want to install
        libmlx.a and/or libmlx_$(HOSTTYPE).a in /usr/X11/lib or /usr/local/lib
        mlx.h in /usr/X11/include or /usr/local/include
        man/man3/mlx*.1 in /usr/X11/man/man3 or /usr/local/man/man3

Olivier CROUZET - 2014-01-06 -
``
