/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#             */
/*   Updated: 2025/11/27 15:27:18 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <limits.h>
# include <math.h>
# include "../My_libft/headers/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define RESET "\e[0;37m"

# define MAP_W 50
# define MAP_H 30

typedef struct s_data	t_data;

# ifdef BONUS

#  define TILE_SIZE 5

typedef struct s_tinfo
{
	int		tex_inf[2];
	t_img	*img;
}	t_tinfo;

# else

#  define TILE_SIZE 15

# endif

typedef struct s_button
{
	int		x;
	int		y;
	int		width;
	int		height;
	char	*img_name;
	void	(*on_click)(t_data *data);
}		t_button;

/* ************************************************************************** */
/*                              EXTERN BUTTONS                                */
/* ************************************************************************** */

extern t_button			g_home_button[];
extern t_button			g_gmd_selector[];
extern t_button			g_setting_menu_button[];
extern t_button			g_pause_button[];
extern t_button			g_death_menu[];
extern t_button			g_win_screen[];

typedef struct s_txt
{
	char	*name;
	char	*path;
	t_img	img;
}	t_txt;

typedef enum e_page_id
{
	HOME_PG,
	GMP_PG,
	SETT_PG,
	GAME_PG,
	PAUSE_PG,
	DEATH_PG,
	WIN_PG,
}	t_page_id;

typedef enum e_texture_id
{
	TEX_NO,
	TEX_SO,
	TEX_WE,
	TEX_EA,
	TEX_COUNT
}	t_texture_id;

typedef enum e_px_type
{
	PX_EMPTY = 0,
	PX_WALL = 1,
	PX_DOOR = 2,
	PX_MOB = 3,
	PX_ITEM = 4
}	t_px_type;

typedef struct s_param
{
	t_data	*data;
	t_img	*dest;
	t_txt	*layer;
	float	factor;
	int		offset[2];
}	t_param;

typedef struct s_win
{
	void	*win;
	void	*mlx;
	t_img	*img;
}	t_win;

typedef struct s_pl
{
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pa;
	float	rot_speed;
	float	mouv_speed;
	float	parralax_x;
	int		pl_height;
	int		is_shooting;
	int		shoot_timer;
	int		shoot_cd_timer;
	int		shoot_cd;
	int		shoot_reload_timer;
	int		shoot_reload;
	int		bullet_count;
	int		chainsaw_offset;
	int		is_alive;
}	t_pl;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_room
{
	int	x;
	int	y;
	int	w;
	int	h;
	int	cx;
	int	cy;
}	t_room;

typedef struct s_map
{
	char	**map;
	int		f_color;
	int		c_color;
	t_txt	textures[4];
	int		height;
	int		width;
}	t_map;

typedef struct s_line
{
	float	dx;
	float	dy;
	float	x;
	float	y;
	float	x_inc;
	float	y_inc;
	int		steps;
}	t_line;

typedef struct s_raycast
{
	float	rx;
	float	ry;
	float	xo;
	float	yo;
	float	atan;
	float	ntan;
	float	ra;
	float	rx_h;
	float	ry_h;
	float	rx_v;
	float	ry_v;
	float	rx_final;
	float	ry_final;
	int		tex_x;
}	t_raycast;

typedef struct s_mouse
{
	int		mouse_x;
	int		mouse_y;
	int		old_mouse_x;
	int		old_mouse_y;
	int		x_accel;
	int		y_accel;
	int		mouse_pressed;
	int		mouse_button_lc;
	int		mouse_button_rc;
	int		button_hovered;
	float	sensitivity;
}	t_mouse;

# ifdef BONUS

typedef struct s_column_info
{
	int		screen_h;
	int		y;
	int		line_h;
	int		start_y;
	int		end_y;
	int		tex_y;
	int		color;
	float	step;
	float	tex_pos;
}	t_column_info;

typedef struct s_mob
{
	float	mx;
	float	my;
	int		hp;
	int		is_alive;
	int		id;
	int		chase;
	int		knockback;
	int		knockback_timer;
	char	*sprite;
	float	size;
}	t_mob;

typedef struct s_px
{
	uint32_t	color;
	float		depth;
	t_px_type	type;
	int			id;
}	t_px;

typedef struct s_f_img
{
	t_px	*pixels;
	t_img	*img;
	int		width;
	int		height;
}	t_f_img;

typedef struct s_data
{
	t_map		*map;
	t_txt		*txt;
	t_win		*win;
	t_img		*ceiling;
	t_f_img		*render_gmp;
	t_page_id	current_pg;
	t_button	*current_buttons;
	int			game_on;
	int			in_game;
	int			slider_button1;
	t_mob		*mob;
	int			mob_count;
	t_raycast	*raycast_f;
	int			slider_button2;
	int			*slider_button;
	t_mouse		mouse;
	int			hud_key_pressed;
	int			pos_y_hud;
	int			win_op;
	int			tilt;
	int			door_state;
	float		offset_door_ratio;
	int			scale;
	int			fps_cap;
	float		fov;
	int			player_hp;
	int			res_x;
	t_pl		player;
	int			shift_is_press;
	int			shot1;
	int			shot2;
	float		xx;
	float		xy;
	int			w_is_press;
	int			s_is_press;
	int			a_is_press;
	int			d_is_press;
	int			p_is_press;
	int			o_is_press;
	int			res_y;
	int			map_w;
	int			map_h;
}	t_data;

# else

typedef struct s_data
{
	t_map	*map;
	t_win	*win;
	int		res_x;
	int		res_y;
	t_pl	player;
	float	fov;
	int		w_is_press;
	int		s_is_press;
	int		a_is_press;
	int		d_is_press;
}	t_data;

# endif

/* ************************************************************************** */
/*                              INIT & PARSING                                */
/* ************************************************************************** */

t_data			*init_data(void);
t_map			*parse_file(int fd);
t_txt			*init_textures(t_data *data);
void			init_textures_mand(t_data *data);
int				check_arg_and_open(int ac, char **av);
char			**getmap(int fd);
int				name_checker(char *str);

/* ************************************************************************** */
/*                              MAP GENERATION                                */
/* ************************************************************************** */

char			**generate_map(int map_w, int map_h);
char			**make_map(t_data *data);
char			**alloc_map(int map_w, int map_h);
void			clean_map(char **map, int map_w, int map_h);
void			setup_player_exit(char **map, int map_w, int map_h);
int				find_player_pos(char **map, int map_w, int map_h, int *pos);
void			find_farthest_point(int **dist, int map_w, int map_h,
					int *exit);
void			get_exit_pos(t_data *data);

/* ************************************************************************** */
/*                              MAP VALIDATION                                */
/* ************************************************************************** */

int				is_valid_map(t_data *data);
int				check_invalid(char **map);
void			check_map_ff(t_data *data, t_map *map);
int				flood_fill_element(char **map, int x, int y, char element);
void			reparse(char **map);
void			reparse_west(char **map, int px);
void			reparse_north(char **map, int py);
void			reparse_south(char **map, int py);
void			reparse_east(char **map, int px);

/* ************************************************************************** */
/*                              ROOM & CORRIDOR                               */
/* ************************************************************************** */

t_room			create_room(char **map, int pos[2], int wh[2], int params[2]);
int				try_place_room(char **map, t_room *rooms, int params[4]);
void			fill_room_borders(char **map, t_room *room, int params[4]);
void			create_corridor(char **map, t_room r1, t_room r2,
					int params[2]);
void			carve_tile(char **map, int pos[2], int map_w, int map_h);
void			carve_horizontal(char **map, int *coords, int params[2]);
void			carve_vertical(char **map, int *coords, int params[2]);

/* ************************************************************************** */
/*                              FLOOD FILL                                    */
/* ************************************************************************** */

int				is_valid(int pos[2], char **map, int **visited, int params[2]);
int				**init_distance_grid(int map_w, int map_h);
void			init_directions(int dirs[4][2]);
void			process_neighbors(char **map, int **dist, t_point *queue,
					int params[4]);
void			flood_fill(char **map, int **dist, t_point *queue,
					int params[4]);

/* ************************************************************************** */
/*                              RAYCASTING                                    */
/* ************************************************************************** */

void			draw_walls_3d(t_data *data);
void			draw_wall_column_txt(t_data *data, int x, float ra);
void			get_distances(t_data *data, float ra, float *dist_h,
					float *dist_v);
float			get_corrected_distance(t_data *data, float ra, float dist);
int				calculate_line_height(t_data *data, float dist_final,
					int *full_h);
float			get_wall_x(t_data *data, float dist[3], float ra);
void			cast_horizontal_ray(t_data *data, float *rx, float *ry,
					float angle);
void			cast_vertical_ray(t_data *data, float *rx, float *ry,
					float angle);

# ifdef BONUS

void			cast_rays(t_data *data, t_raycast *raycast);
void			cast_doors_rays(t_data *data, t_raycast *raycast);
void			calculate_distances(t_data *data, t_raycast *raycast,
					float *dist_h, float *dist_v);
void			get_final_distance(t_data *data, float dist[2], float ra,
					float *dist_final);
void			calculate_wall_dimensions(t_data *data, float dist_final,
					int *line[2], int factor);
void			cast_horizontal_door_ray(t_data *data, float *rx, float *ry,
					float angle);
void			cast_vertical_door_ray(t_data *data, float *rx, float *ry,
					float angle);
void			cast_horizontal_mob_ray(t_data *data, float *rx, float *ry,
					float angle);
void			cast_vertical_mob_ray(t_data *data, float *rx, float *ry,
					float angle);

# endif

/* ************************************************************************** */
/*                              RENDERING                                     */
/* ************************************************************************** */

int				render_frame(t_data *data);
void			render_scene(t_data *data);
void			render_img(t_data *data);
void			clear_frame(t_data *data);
int				is_valid_render_data(t_data *data);

# ifndef BONUS

void			render_column(t_data *data, t_img *img, int x[2],
					int full_line_h);
t_txt			*find_wall_txt(t_data *data, float dist_h, float dist_v,
					float ra);

# else

void			render_column(t_data *data, int value[5], t_txt *txt,
					float dist_final);
void			render_gameplay(t_data *data);
void			render_gameplay_full(t_data *data);
t_txt			*find_wall_txt(t_data *data, float dist_h, float dist_v,
					t_raycast *ray);
void			get_texture_info(t_data *data, float dist[2],
					t_raycast *raycast, t_txt **txt);
void			store_ray_coords(t_data *data, int i, t_raycast *ray,
					float dists[2]);
void			render_depth(t_f_img *image);
void			pp_depth(t_f_img *f_img);

# endif

/* ************************************************************************** */
/*                              COLUMN RENDERING                              */
/* ************************************************************************** */

int				get_line_offset(t_data *data, int full_line_h);
float			get_initial_tex_pos(int line_off, float step);
int				get_start_y(int line_off);
int				get_end_y(t_data *data, int line_off, int full_line_h);
void			draw_wall_column(t_data *data, int value[5], t_img *img,
					float depth);
void			draw_door_column(t_data *data, int value[5], t_img *img,
					float depth);

# ifdef BONUS

void			init_column_info(t_column_info *c, int line_h, t_img *img);
void			adjust_column_bounds(t_column_info *c, int line_off);
void			prepare_door_column(t_column_info *c, int line_h, int line_off,
					t_img *img);
void			adjust_door_offset(t_column_info *c, int value[5],
					t_data *data);

# endif

/* ************************************************************************** */
/*                              FLOOR & CEILING                               */
/* ************************************************************************** */

# ifdef BONUS

void			draw_floor(t_data *data, int x, int y_start);
void			draw_ceiling(t_data *data, int x, int y_end, t_img *ceiling);
void			draw_ceiling_img(t_data *data);
void			draw_ceiling_to_screen(t_data *data);
void			get_floor_pos(double *fx, double *fy, t_data *data,
					double *ray);

# else

void			draw_ceiling_to_screen(t_data *data);

# endif

/* ************************************************************************** */
/*                              TEXTURES                                      */
/* ************************************************************************** */

int				get_texture_x(t_img *img, float wall_x);
float			get_wall_x_coord(float dist_h, float dist_v, float hit[2],
					float ra);
t_txt			*find_texture(t_txt *textures, const char *name);
void			print_texture_set(t_txt *txt);
void			copy_texture_to_img(t_img *src, t_img *dst, int pos_x,
					int pos_y);

/* ************************************************************************** */
/*                              PLAYER                                        */
/* ************************************************************************** */

void			get_player_original_pos(t_data *data);
char			get_player_pos(char **map, int *x, int *y);
int				is_player(char c);
void			mouv_player(t_data *data);
void			handle_movement(t_data *data);
void			handle_rotation(t_data *data);
void			update_head_bob(t_data *data, int *up);

# ifdef BONUS

void			monitor_player(t_data *data);
void			is_player_hit(t_data *data);

# endif

/* ************************************************************************** */
/*                              COLLISION                                     */
/* ************************************************************************** */

int				check_collision(t_data *data, float pos[2], float r, char c);
int				check_wall_collision(t_data *data, float x, float y, float r);
int				check_open_door_collision(t_data *data, float x, float y,
					float r);
int				is_wall(t_data *data, int x, int y);
int				is_wall_hit(t_data *data, int mx, int my);
int				is_door_hit(t_data *data, int mx, int my);
int				is_valid_pos(int x, int y, int map_w, int map_h);

/* ************************************************************************** */
/*                              MOBS (BONUS)                                  */
/* ************************************************************************** */

# ifdef BONUS

void			init_mob(t_data *data);
void			spawn_random_mob(t_data *data);
int				is_mob(t_data *data, int mx, int my);
void			place_enemies(char **map, t_room *room);
void			draw_mobs(t_data *data);
void			mob_path(t_data *data);
float			calculate_mob_distance(t_data *data, int i);
void			knockback(t_data *data);
void			get_mob_ratios(t_txt *tex, int *bounds, float *ratios, int x);

# endif

/* ************************************************************************** */
/*                              WEAPONS & ACTIONS                             */
/* ************************************************************************** */

# ifdef BONUS

void			shooting(t_data *data);
void			use_chainsaw(t_data *data);
void			action_key(t_data *data);

# endif

/* ************************************************************************** */
/*                              DRAWING                                       */
/* ************************************************************************** */

void			draw_to_img(t_data *data, const char *txt_name, int pos_x,
					int pos_y);
void			draw_sprite(t_data *data, float pos[2], char *sprite_name,
					float size);
void			draw_line(t_win *win, float x[2], float y[2], int color);
void			draw_rect(t_data *data, int pos[2], int scale[2], int color);
void			draw_rect_fill(t_data *data, int pos[2], int scale[2],
					int color);
void			draw_circle(t_data *img, int i[4], int color);
void			draw_tile(t_win *win, int x, int y, int color);
void			put_pixel(t_img *img, int x, int y, uint32_t color);
void			put_pixel_up(char *img, int *vars);
unsigned int	get_pixel_up(char *img, int *vars);
uint32_t		get_pixel(t_img *img, int x, int y);

# ifdef BONUS

void			draw_px_info(t_data *data, int index, int color,
					float *ratios);

# endif

/* ************************************************************************** */
/*                              MINIMAP & HUD                                 */
/* ************************************************************************** */

void			draw_map(t_win *win, char **map, int offset_x, int offset_y);
void			draw_mini_map_centered(t_data *data, int radius, int thickness,
					int pos[2]);
void			draw_player(t_data *data, int offset_x, int offset_y);
void			draw_rays(t_data *data, int offset_x, int offset_y);
void			draw_rays_3d(t_data *data, int offset_x, int offset_y);

# ifdef BONUS

void			draw_rays_3d_bonus(t_data *data, int offset_x, int offset_y);
void			draw_hud(t_data *data);
void			draw_hud_background(t_data *data);
void			draw_exit(t_data *data);

# endif

/* ************************************************************************** */
/*                              MENUS & UI                                    */
/* ************************************************************************** */

void			draw_home_page(t_data *data);
void			draw_game_mode(t_data *data);
void			draw_setting(t_data *data);
void			draw_pause_menu(t_data *data);
void			draw_death_menu(t_data *data);
void			draw_win_screen(t_data *data);
void			draw_background_mand(t_data *data);
void			render_home_pages(t_data *data);
void			render_pause(t_data *data);
void			draw_mouse_icon(t_data *data);
void			highlight_button(t_data *data, t_button *b);
void			highlight_hovered_button(t_data *data);
void			print_image_window_simple(t_data *data, const char *path,
					int x, int y);
void			put_string_to_img(t_data *data, int pos[2], uint32_t color,
					char *str);

/* ************************************************************************** */
/*                              MENU ACTIONS                                  */
/* ************************************************************************** */

void			go_play_menu(t_data *data);
void			go_setting_menu(t_data *data);
void			play_mainmenu(t_data *data);
void			play_mandatory(t_data *data);
void			play_endless_mode(t_data *data);
void			play_survivor_mode(t_data *data);
void			survivor_map(t_data *data);
void			back_to_main(t_data *data);
void			resize_640(t_data *data);
void			resize_1280(t_data *data);
void			resize_1920(t_data *data);
void			resize_window(t_data *data, int resx, int resy);
void			retry_game(t_data *data);
void			new_map_random(t_data *data);

/* ************************************************************************** */
/*                              INPUT HANDLING                                */
/* ************************************************************************** */

int				handle_key_press(int keycode, t_data *data);
int				handle_key_release(int keycode, t_data *data);
int				handle_key(int keycode, void *param);
void			handle_key_game(t_data *data);
void			handle_escape_key(t_data *data);
int				handle_mouse_move(int x, int y, t_data *data);
int				handle_mouse_click(int button, int x, int y, t_data *data);
int				handle_mouse_press(int button, int x, int y, t_data *data);
int				handle_mouse_release(int button, int x, int y, t_data *data);
int				handle_close(void *param);

/* ************************************************************************** */
/*                              GAME LOOP                                     */
/* ************************************************************************** */

void			mlx_game_loop(t_data *data);
void			setup_hooks(t_data *data);
void			create_windows(t_win *win, t_data *data);

# ifdef BONUS

void			animate_door(t_data *data);

# endif

/* ************************************************************************** */
/*                              UTILITIES                                     */
/* ************************************************************************** */

float			normalize_angle(float angle);
long			get_time_ms(void);
void			calculate_fps(long *prev, float *fps, long current);
void			cap_framerate(t_data *data, long elapsed);
void			init_rand(void);
int				get_rand_d(int min, int max);
float			get_rand_f(float min, float max);
void			init_line_params(t_line *line, float x1, float y1);
char			*ft_strcpy(char *dest, char *src);
int				ft_strcmp(char *s1, char *s2);
char			*ft_sprintf(const char *format, ...);
int				is_line_empty(char *line);
void			fill_map_row(char *row, int map_w);
void			get_img_size(char **element, int size[2]);

# ifdef BONUS

void			compute_ratios(float ratios[2], t_txt *tex, int bounds[7]);
int				get_tex_coord(int screen, int start, float ratio, int max);
int				get_screen_x(float relative_angle, float fov);
float			get_angle_to_sprite(t_data *data, float x, float y);
float			calc_distance(t_data *data, float x, float y);
float			get_relative_angle(t_data *data, int i);

# endif

/* ************************************************************************** */
/*                              COLOR & EFFECTS                               */
/* ************************************************************************** */

int				get_color_map(char c);
uint32_t		depth_render(uint32_t color, int ray_length);
void			darken_image(t_img *img, float factor);
void			upscale(t_data *data);

/* ************************************************************************** */
/*                              MEMORY & CLEANUP                              */
/* ************************************************************************** */

void			free_tab(char **map);
void			free_map(char **map);
void			free_textures(t_txt *textures);
void			free_textures_mand(t_txt *textures);
void			free_map_content(t_data *data, t_map *map);
void			free_map_struct(t_data *data, t_map *map);
void			free_data_mand(t_data *data);
char			**ft_realloc(char **map, int size);
char			**allocate_clone(char **map);
char			**clone_map(char **map);
void			clean_windows(t_win *win);
void			clean_data(t_data *data);
void			cleanup_data(t_data *data);
void			clean_exit_mand(t_data *data);
int				clean_and_exit(t_data *data, int exit_code);
void			clear_and_exit(t_data *data);

/* ************************************************************************** */
/*                              ROOM VALIDATION                               */
/* ************************************************************************** */

int				is_too_close_y(t_room *rooms, int room_count, int y, int h);
int				is_too_close_x(t_room *rooms, int room_count, int x, int w);

/* ************************************************************************** */
/*                              DEBUG                                         */
/* ************************************************************************** */

void			print_map(char **map);

/* ************************************************************************** */
/*                              UNUSED                                        */
/* ************************************************************************** */

# ifdef BONUS

void			do_nothing(t_data *data);

# endif

#endif