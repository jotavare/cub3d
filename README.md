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

## TEAM
- [Pedro Mota](https://github.com/peterbikes) `github` [**maricard**](https://profile.intra.42.fr/users/psotto-m) `intra`
- [Nuno Jesus](https://github.com/jotavare) `github` [**ncarvalh**](https://profile.intra.42.fr/users/jotavare) `intra`

## COMPILATION AND EXECUTION
#### 1º - Clone the repository
```bash
git clone git@github.com:jotavare/cub3d.git
```

#### 2º - Enter the project folder and run `make mlx`
> **Important:** This rule is not mandatory but necessary to run the game.
```bash
cd cub3d/cub3d
make mlx
make re
```

#### 3º - Run the game with a map of your choice
```bash
./cub3d [map.cub]
```

#### MAKEFILE RULES

`make` - Compile so_long files.

`make all`  - Compile mandatory files.

`make clean`  - Delete all .o (object files) files.

`make fclean`  - Delete all .o (object files) and .a (executable) files.

`make re` - Use rules `fclean` + `all`.

## MANDATORY
#### Main
- [x] Must use MiniLibX library;
- [x] The game window must remain smooth: changing to another window, minimizing, etc;
- [x] Display different wall textures that vary depending on which side the wall is facing (North, South, East, West);
- [x] Must be able to set the floor and ceiling colors to two different ones;

#### WINDOW AND KEYS
- [x] Displays the image in a window;
- [x] Left and right arrow keys must allow you to look left and right in the maze.
- [x] The `W`, `A`, `S`, and `D` keys must allow you to move the point of view through the maze.
- [x] Pressing `ESC` or clicking on the `cross` on the window’s frame must close the window and quit the program cleanly.

#### MAP COMPONENTS
- [x] The program has to take as a parameter a map description file ending with the `.cub` extension.
- [x] The map must be composed of only 6 possible characters.

| Characters | Description |
| :--: | :--: |
| `0`               | Empty space.                           |
| `1`               | Wall.                                  |
| `N` `S` `E` `W`   | Player start position and orientation. |

#### MAP PARSING
- [x] The map must be closed/surrounded by walls, if not, the program must return an error.
- [x] Except for the map content, each type of element can be separated by one or more empty line(s).
- [x] Except for the map content, which always has to be the last, each type of element can be set in any order in the file.
- [x] Except for the map, each type of information from an element can be separated by one or more space(s).
- [x] The program must be able to parse any kind of map, as long it respects the rules.
- [x] If an error/misconfiguration is encountered, it should return `Error\n` followed by an explicit message.
- [x] Each element (except the map) first information is the type identifier (composed by one or two character(s)), followed by all specific informations for eachobject

| Name | Example | Identifier | Information |
| :--: | :--: | :--: | :--: |
| North texture: | `NO ./path_to_the_north_texture` | NO | Path to the north texure.                  |
| South texture: | `SO ./path_to_the_south_texture` | SO | Path to the south texure.                  |
| West texture:  | `WE ./path_to_the_west_texture`  | WE | Path to the west texure.                   |
| East texture:  | `EA ./path_to_the_east_texture`  | EA | Path to the east texure.                   |
| Floor color:   | `F 220,100,0`                    | F  | R,G,B colors in range [0,255]: 0, 255, 255 |
| Ceiling color: | `C 225,30,0`                     | C  | R,G,B colors in range [0,255]: 0, 255, 255 |

Example of a valid `.cub` map:
```bash
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## BONUS
- [x] Wall collisions.
- [x] A minimap system.
- [ ] Doors which can open and close.
- [ ] Animated sprite.
- [ ] Rotate the point view with the mouse.

## NORMINETTE
At 42 School, it is expected that almost every project is written in accordance with the Norm, which is the coding standard of the school.

```
- No for, do...while, switch, case, goto, ternary operators and variable-length arrays are allowed
- Each function must be a maximum of 25 lines, not counting the function's curly brackets
- Each line must be at most 80 columns wide, comments included
- A function can take 4 named parameters maximum
- No assigns and declarations in the same line (unless static)
- You can't declare more than 5 variables per function
- ...
```

* [42 Norms](https://github.com/jotavare/jotavare/blob/main/42/pdf/en_norm.pdf) - Information about 42 code norms. `PDF`
* [Norminette](https://github.com/42School/norminette) - Tool by 42, to respect the code norm. `GitHub`
* [42 Header](https://github.com/42Paris/42header) - 42 header for Vim. `GitHub`

## LICENSE
<p>
This work is published under the terms of <a href="https://github.com/jotavare/jotavare/blob/main/LICENSE">42 Unlicense</a>.
</p>