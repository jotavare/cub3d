#!/bin/bash

# ---------------------------------------------------------------------------- #
#                                    Colors                                    #
# ---------------------------------------------------------------------------- #

DEF_COLOR='\033[0;39m'
BLACK='\033[0;30m'
RED='\033[1;91m'
GREEN='\033[1;92m'
YELLOW='\033[0;93m'
BLUE='\033[0;94m'
MAGENTA='\033[0;95m'
CYAN='\033[0;96m'
GRAY='\033[0;90m'
WHITE='\033[0;97m'

textures=(
	"./textures/north.xpm"
	"./textures/south.xpm"
	"./textures/east.xpm"
	"./textures/west.xpm"
	"./textures/x"
	"./textures/north_oversize.xpm"
	"./textures/west_undersize.xpm"
)

invalid_args=(
	""
	" "
	"'' ''"
	'"./maps/valid/cheese_maze.cub" "./maps/valid/creepy.cub"'
	"./maps/valid/filenotfound"
	"./maps/foldernotfound/"
	"."
	"./"
	"/"
	"//"
	"/ /"
	".cub"
)

valid_maps=(
	"./maps/valid/cheese_maze.cub"
	"./maps/valid/creepy.cub"
	"./maps/valid/dungeon.cub"
	"./maps/valid/inner_walls_multi_sections.cub"
	"./maps/valid/inner_walls.cub"
	"./maps/valid/library.cub"
	"./maps/valid/map_whitespace_left.cub"
	"./maps/valid/matrix.cub"
	"./maps/valid/sad_face.cub"
	"./maps/valid/square_map.cub"
	"./maps/valid/subject_map.cub"
	"./maps/valid/test_map_hole.cub"
	"./maps/valid/test_map.cub"
	"./maps/valid/test_pos_bottom.cub"
	"./maps/valid/test_pos_left.cub"
	"./maps/valid/test_pos_right.cub"
	"./maps/valid/test_pos_top.cub"
	"./maps/valid/test_textures.cub"
	"./maps/valid/test_whitespace.cub"
	"./maps/valid/works.cub"
	"./maps/valid/triangle.cub"
	"./maps/valid/triangle_multi.cub"
)

invalid_maps=(
	"./maps/invalid/.cub"
	"./maps/invalid/.cul"
	"./maps/invalid/color_invalid_rgb.cub"
	"./maps/invalid/color_missing_ceiling_rgb.cub"
	"./maps/invalid/color_missing_floor_rgb.cub"
	"./maps/invalid/color_missing.cub"
	"./maps/invalid/color_none.cub"
	"./maps/invalid/duplicated_setting.cub"
	"./maps/invalid/empty.cub"
	"./maps/invalid/file_letter_end.cub"
	"./maps/invalid/filetype_missing"
	"./maps/invalid/filetype_wrong.buc"
	"./maps/invalid/inner_walls_missing_open.cub"
	"./maps/invalid/inner_walls_missing.cub"
	"./maps/invalid/inner_walls_multi_sections_open.cub"
	"./maps/invalid/invalid_map_char.cub"
	"./maps/invalid/map_first.cub"
	"./maps/invalid/map_middle.cub"
	"./maps/invalid/map_missing.cub"
	"./maps/invalid/map_only.cub"
	"./maps/invalid/map_too_small.cub"
	"./maps/invalid/missing_wall_outer_bottom1.cub"
	"./maps/invalid/missing_wall_outer_bottom2.cub"
	"./maps/invalid/missing_wall_outer_right.cub"
	"./maps/invalid/missing_wall_outer_top1.cub"
	"./maps/invalid/missing_wall_outer_top2.cub"
	"./maps/invalid/player_multiple.cub"
	"./maps/invalid/player_none.cub"
	"./maps/invalid/player_on_edge.cub"
	"./maps/invalid/subject_map_tabs.cub"
	"./maps/invalid/textures_dir.cub"
	"./maps/invalid/textures_dir2.cub"
	"./maps/invalid/textures_duplicates.cub"
	"./maps/invalid/textures_forbidden.cub"
	"./maps/invalid/textures_invalid.cub"
	"./maps/invalid/textures_missing.cub"
	"./maps/invalid/textures_multiple_words.cub"
	"./maps/invalid/textures_none.cub"
	"./maps/invalid/textures_not_xpm.cub"
	"./maps/invalid/textures_value_missing.cub"
	"./maps/invalid/wall_hole_east.cub"
	"./maps/invalid/wall_hole_north.cub"
	"./maps/invalid/wall_hole_south.cub"
	"./maps/invalid/wall_hole_west.cub"
	"./maps/invalid/wall_none.cub"
	"./maps/invalid/wrong_setting.cub"
	"./maps/invalid/triangle_open.cub"
	"./maps/invalid/triangle_multi_open.cub"
	"./maps/invalid/broken_xpm.cub"
	"./maps/valid/xpm_wrong_size.cub"
)

# ---------------------------------------------------------------------------- #
#                                    Tester                                    #
# ---------------------------------------------------------------------------- #

printf ${BLUE}"\n-------------------------------------------------------------\n"${DEF_COLOR};
printf ${YELLOW}"\n\t\tTEST CREATED BY: "${DEF_COLOR};
printf ${CYAN}"NUMARTIN\t\n"${DEF_COLOR};
printf ${BLUE}"\n-------------------------------------------------------------\n"${DEF_COLOR};

# check if textures files are present
for texture in "${textures[@]}"
do
	if [ ! -f $texture ]; then
		printf ${RED}"File missing: ${texture}. Make sure to include the textures folder to the root of your project\n";
		exit 1;
	fi
done


printf ${BLUE}"\n-------------------------------------------------------------\n"${DEF_COLOR};
printf ${BLUE}"\n\t\t\tINVALID ARGS\t\n"${DEF_COLOR};
printf ${BLUE}"\n-------------------------------------------------------------\n\n"${DEF_COLOR};

for arg in "${invalid_args[@]}"
do
	N=$(./cub3d $arg | grep -x "Error" | wc -l)
	if [ $N -eq 0 ]; then
		printf "${RED}[KO]${DEF_COLOR}";
	else
		printf "${GREEN}[OK]${DEF_COLOR}";
	fi
	R=$(valgrind --leak-check=full --show-leak-kinds=all --log-fd=1 ./cub3d $arg | grep -Ec 'no leaks are possible|ERROR SUMMARY: 0')
	if [[ $R == 2 ]]; then
		printf "${GREEN}[MOK]${DEF_COLOR}";
	else
		printf "${RED}[KO LEAKS]${DEF_COLOR}";
	fi
	printf " args: ${arg}\n";
done

printf ${BLUE}"\n-------------------------------------------------------------\n"${DEF_COLOR};
printf ${BLUE}"\n\t\t\tINVALID MAPS\t\n"${DEF_COLOR};
printf ${BLUE}"\n-------------------------------------------------------------\n\n"${DEF_COLOR};

for map in "${invalid_maps[@]}"
do
	if [ ! -f $map ]; then
		printf ${RED}"File missing: ${map}.\n";
		exit 1;
	fi
	N=$(./cub3d $map | grep -x "Error" | wc -l)
	if [ $N -eq 0 ]; then
		printf "${RED}[KO]${DEF_COLOR}";
	else
		printf "${GREEN}[OK]${DEF_COLOR}";
	fi
	R=$(valgrind --leak-check=full --show-leak-kinds=all --log-fd=1 ./cub3d $map | grep -Ec 'no leaks are possible|ERROR SUMMARY: 0')
	if [[ $R == 2 ]]; then
		printf "${GREEN}[MOK]${DEF_COLOR}";
	else
		printf "${RED}[KO LEAKS]${DEF_COLOR}";
	fi
	printf " ${map}\n";
done

printf ${BLUE}"\n-------------------------------------------------------------\n"${DEF_COLOR};
printf ${BLUE}"\n\t\t\tVALID MAPS\t\n"${DEF_COLOR};
printf ${BLUE}"\n-------------------------------------------------------------\n\n"${DEF_COLOR};

for map in "${valid_maps[@]}"
do
	if [ ! -f $map ]; then
		printf ${RED}"File missing: ${map}.\n";
		exit 1;
	fi
	N=$(./cub3d $map | grep -x "Error" | wc -l)
	if [ $N -eq 0 ]; then
		printf "${GREEN}[OK]${DEF_COLOR}";
	else
		printf "${RED}[KO]${DEF_COLOR}";
	fi
	R=$(valgrind --leak-check=full --show-leak-kinds=all --log-fd=1 ./cub3d $map | grep -Ec 'no leaks are possible|ERROR SUMMARY: 0')
	if [[ $R == 2 ]]; then
		printf "${GREEN}[MOK]${DEF_COLOR}";
	else
		printf "${RED}[KO LEAKS]${DEF_COLOR}";
	fi
	printf " ${map}\n";
done
