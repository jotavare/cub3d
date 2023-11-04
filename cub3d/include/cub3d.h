/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:08:28 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/04 18:10:01 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// [LIBRARIES] //
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "structs.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

// [MACROS] //
# define WIN_W 1280
# define WIN_H 720
# define PI 3.14159265358979323846
# define RES 64
# define MINIMAP_SCALE 10

# define PLAYER_SPEED 4.0
# define PLAYER_ANGLE_SPEED 3.0
# define SLIDE_DISTANCE 0.1

// [ALGORITHM] //
// check_wall.c
t_ray_data	*vertical_wall_check(t_cub3d *data, t_ray_data *ray_elem);
t_ray_data	*horizontal_wall_check(t_cub3d *data, t_ray_data *ray_elem);
int			map_coords(int x, int y, int w, int h);
void		calc_horizon_dist_wall(t_player_data *player, t_ray_data *ray,
				float atan);
void		calc_vertical_dist_wall(t_player_data *player, t_ray_data *ray,
				float atan);

// render_3d_ray.c
t_texture	*get_ray_texture(t_cub3d *data, t_ray_data ray);
int			ray_hit_position(t_ray_data ray);
void		render_3d_ray(t_cub3d *data, t_ray_data ray, int ray_num);
void		render_texture_pillar(t_ray_data ray, t_texturing_data *t_data);
void		frame_texture_line(t_texturing_data *text_data,
				t_pixel_pos window_src, int window_line_h, int texture_x);

// init_player.c
float		start_point_angle(int start);
void		initialize_player(t_cub3d *data);

// ray.c
t_ray_data	shortest_line(t_player_data *p, t_ray_data h_inter,
				t_ray_data v_inter);
int			pew_pew_rays(t_cub3d *data);
double		ray_angle(t_cub3d *data, int window_x);
float		pythagoras_distance(float ax, float ay, float bx, float by);
void		render_3d_world(t_cub3d *data);

// [CUB3D] //
// cub3d_utilities.c
int			inicialize_mlx(t_cub3d *cub3d);
float		min_float(float a, float b);
void		display_error(char *str);
void		destroy_mlx(t_cub3d cub3d);

// player_movement.c
float		max_valid_x_move(t_cub3d *data, float x_want);
float		max_valid_y_move(t_cub3d *data, float y_want);
void		update_player_pos(t_cub3d *data);
void		update_player_plane_vector(t_cub3d *data);
void		player_move(t_cub3d *data, float x_add, float y_add);

// cub3d.c
int			cub3d_loop(t_cub3d *cub3d);
void		cub3d_free(t_cub3d *cub3d);
void		set_hooks(t_cub3d *cub3d);

// key_events.c
int			handle_keydown(int keysym, t_cub3d *cub3d);
int			handle_keyup(int keysym, t_cub3d *cub3d);
int			handle_window_kill(t_cub3d *cub3d);

// [PARSING] //
// file_validation.c
int			valid_data_line(char *line);
int			valid_empty_line(char *line);
int			valid_file_format(char *file, t_parse_data *parse_data);
int			valid_cub_extension(char *filename);

// map_dimensions.c
int			valid_map_char(char c);
int			calc_map_line_length(char *line);
int			map_dimensions_file(char *file, t_parse_data *parse_data);
void		end_of_file(int fd);

// map_inicialize.c
int			initialize_map(t_parse_data *parse_data);
int			read_parse_file(char *file, t_parse_data *parse_data);
void		free_2d_map(int **map);
void		free_parsing_data(t_parse_data *parse_data);

// map_populate.c
void		fill_map_row(int *row, char *line);
int			read_populate_map_file(char *file, t_parse_data *parse_data);

// map_validation.c
int			invalid_blocks_found(t_parse_data *parse_data);
int			verify_enclosed_space(t_parse_data *parse_data, int x, int y);
int			check_map_holes(t_parse_data *parse_data);
int			count_spawn_points(t_parse_data *parse_data);
int			validate_game_map(t_parse_data *parse_data);

// process_data.c
int			process_data_file_line(char *file, t_parse_data *parse_data);
int			read_color_split_line(char **line_split, t_parse_data *parse_data);
int			read_text_split_line(char **line_split, t_parse_data *parse_data);
int			check_duplicate_line(char *line, t_parse_data *parse_data);
int			process_parsed_data_line(char *line, t_parse_data *parse_data);

// validation_handling.c
int			line_data_check(char *line);
void		assign_error_code(t_parse_data *parse_data, int n);
void		display_parsing_error(int err);
void		output_game_map(t_parse_data *parse_data);

// validation_utilities.c
int			data_missing(t_parse_data *parse_data);
int			valid_texture_line(char *line);
int			valid_color_line(char *line);
int			valid_color(char **split);

// [RENDERING] //
// 2d.c
void		render_ceiling_floor(t_cub3d *cub3d);

// minimap.c
void		display_minimap(t_cub3d *cub3d);
void		render_frame_2d_map(t_cub3d *cub3d);
void		render_frame_player(t_cub3d *cub3d, float y_start, float x_start);
void		render_frame_block(t_cub3d *cub3d, int y_start, int x_start,
				int color);

// texture.c
int			initialize_texture_loading(t_cub3d *cub3d);
int			retrieve_texture_pixel(t_texture texture, t_pixel_pos p);
void		initialize_texture_data(t_cub3d *cub3d);

// utilities.c
void		frame_draw_pixel(t_frame frame, t_pixel_pos p, int color);
void		clear_frame(t_frame frame);
void		put_frame_to_window(t_cub3d *cub3d);

#endif
