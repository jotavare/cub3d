- sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
- [https://www.youtube.com/watch?v=bYS93r6U0zg](https://www.youtube.com/watch?v=bYS93r6U0zg)
- [https://github.com/42Paris/minilibx-linux](https://github.com/42Paris/minilibx-linux)
- [x.org](https://www.x.org/wiki/)
- [https://www.x.org/releases/X11R7.6/doc/libX11/specs/libX11/libX11.html](https://www.x.org/releases/X11R7.6/doc/libX11/specs/libX11/libX11.html)
- https://www.youtube.com/watch?v=nKcfhI1B4mA
- cc main.c -Lminilibx-linux -lmlx_Linux -lX11 -lXext

bash´´´
gcc program.c -Lminilibx-linux -lmlx_Linux -o process -lX11 -lXext

Do make into the minilibx

minilibx-linux-> Path with the lib
mlx_Linux-> Name of the archive file (libmlx_Linux.a)
´´´
