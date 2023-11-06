<p align="center">
  <img src="https://github.com/jotavare/jotavare/blob/main/42/banner/new/42_cub3d_banner_new.png">
</p>

<p align="center">
	<img src="https://img.shields.io/badge/status-finished-success?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/badge/evaluated-04%20%2F%2011%20%2F%202023-success?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/badge/score-110%20%2F%20100-success?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/github/languages/top/jotavare/cub3d?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/github/last-commit/jotavare/cub3d?color=%2312bab9&style=flat-square"/>
	<a href='https://www.linkedin.com/in/joaoptoliveira' target="_blank"><img alt='Linkedin' src='https://img.shields.io/badge/LinkedIn-100000?style=flat-square&logo=Linkedin&logoColor=white&labelColor=0A66C2&color=0A66C2'/></a>
	<a href='https://profile.intra.42.fr/users/jotavare' target="_blank"><img alt='42' src='https://img.shields.io/badge/Porto-100000?style=flat-square&logo=42&logoColor=white&labelColor=000000&color=000000'/></a>
</p>

<p align="center">
	<a href="#about">About</a> •
	<a href="#how-to-use">How to use</a> •
	<a href="#license">License</a>
</p>

## ABOUT
Cub3D is a graphics programming project where I dived into raycasting to create a 3D game in C using the minilibx library. I learned about raycasting, basic algorithms, rendering 3D environments, textures, windows, colors, events, shape filling, wall collision, map parsing, mini-map, ...

This project is inspired by the world-famous Wolfenstein 3D game, developed by Id Software by the über famous John Carmack and John Romero, published in 1992 by Apogee Software, Wolfenstein 3D is the first true “First Person Shooter” in the history of video games.

<a href="http://users.atw.hu/wolf3d/">Play the original game.</a>

<a href="https://github.com/jotavare/netpractice/blob/main/subject/en_subject_cub3d.pdf">Click here</a> for the subject of this project.

## Common Instructions
- [x] Written in C;
- [x] Norminette validated;
- [x] No segmentation fault, bus error, double free, etc;
- [x] All heap allocated memory space properly freed (no leaks);
- [x] Makefile should compile the source files, use cc and flags (-Wall, -Wextra and -Werror);
- [x] Makefile shouldn't relink and must contain the rules $(NAME), all, clean, fclean and re;
- [ ] Mandatory and bonus part evaluation is done separately. Different files, headers and with a bonus rule on the Makefile (_bonus.{c/h});

- sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
- [https://www.youtube.com/watch?v=bYS93r6U0zg](https://www.youtube.com/watch?v=bYS93r6U0zg)
- [https://github.com/42Paris/minilibx-linux](https://github.com/42Paris/minilibx-linux)
- [x.org](https://www.x.org/wiki/)
- [https://www.x.org/releases/X11R7.6/doc/libX11/specs/libX11/libX11.html](https://www.x.org/releases/X11R7.6/doc/libX11/specs/libX11/libX11.html)
- https://www.youtube.com/watch?v=nKcfhI1B4mA
- make inside the minilibx folder
- cc main.c -Lminilibx-linux -lmlx_Linux -lX11 -lXext
- https://www.youtube.com/watch?v=iz958I8Xb2g&t=9s
- https://github.com/terry-yes/mlx_example

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