#ifndef CUB3D_H
# define CUB3D_H


# include <stdio.h>
# include "../My_libft/headers/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
#include <limits.h>
#include <math.h>
		
//COLORS
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define RESET "\e[0;37m"


#define MAP_W 50
#define MAP_H 30
// #define M_PI = 3.14159

typedef struct s_data t_data;

#ifdef BONUS
	
#define TILE_SIZE 5   // Taille de chaque case en pixels

typedef struct s_tinfo
{
	int		tex_inf[2];
	t_img	*img;
} t_tinfo;

#else

#define TILE_SIZE 15   // Taille de chaque case en pixels

#endif
typedef struct s_button
{
	int x;
	int y;
	int width;
	int height;
	char *img_name;
	void (*on_click)(t_data *data);
} t_button;

extern t_button g_home_button[];
extern t_button gmd_selector[];
extern t_button setting_menu_button[];
extern t_button pause_button[];

typedef struct s_txt
{
    char *name;
    char *path;
	t_img img;
} t_txt;

typedef enum e_page_id
{
	HOME_PG,
	GMP_PG,
	SETT_PG,
	GAME_PG,
	PAUSE_PG
}	t_page_id;


typedef enum e_texture_id
{
    TEX_NO,
    TEX_SO,
    TEX_WE,
    TEX_EA,
    TEX_COUNT
} t_texture_id;

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
	float 	pdy;
	float	 pa;
	float 	rot_speed;
	float	mouv_speed;
	float	parralax_x;
	int		pl_height;
	int		is_shooting;
	int		shoot_timer;
	int		shoot_cd_timer;
	int		shoot_cd;
	int		shoot_reload_timer;
	int		shoot_reload;
	int 	bullet_count;
}	t_pl;

typedef struct s_room 
{
    int x, y;   // coin haut gauche
    int w, h;   // largeur / hauteur
    int cx, cy; // centre
} t_room;

typedef struct s_map
{
    char    **map;
    int     f_color;
    int     c_color;
    t_txt   textures[4]; 
	int		height;
	int		width;
}   t_map;

typedef struct s_line
{
    float   dx;
    float   dy;
    float   x;
    float   y;
    float   x_inc;
    float   y_inc;
    int     steps;
}   t_line;

typedef struct s_raycast
{
	float   rx;
    float   ry;
    float   xo;
    float   yo;
    float   atan;
    float   ntan;
    float   ra;
    float   rx_h;
    float   ry_h;
    float   rx_v;
    float   ry_v;
    float   rx_final;
    float   ry_final;
	int 	tex_x;
}   t_raycast;

typedef struct s_mouse
{
	int		mouse_x;
	int		mouse_y;
	int		old_mouse_x;
	int 	old_mouse_y;
	int		x_accel;
	int		y_accel;
	int		mouse_pressed;
	int		button_hovered;
	float	sensitivity;

}	t_mouse;

#ifdef BONUS


typedef struct s_column_info
{
	int screen_h;   // hauteur écran (ex: 480)
	int y;          // index de boucle (ligne courante)
	int line_h;     // hauteur de la ligne à dessiner
	int start_y;    // position de départ (corrigée)
	int end_y;      // position de fin (corrigée)
	int tex_y;      // coordonnée y dans la texture
	int color;      // couleur finale
	float step;     // rapport texture -> écran
	float tex_pos;  // position actuelle dans la texture
}	t_column_info;


typedef struct s_mob
{
	float	mx;
	float	my;
	int		hp;
	int		is_alive;
	int 	id;
	int		chase;
	int		knockback;
	int		knockback_timer;
	char	*sprite;
	float	size;
}	t_mob;

typedef enum e_px_type
{
    PX_EMPTY = 0,
    PX_WALL = 1,
    PX_DOOR = 2,
    PX_MOB = 3,
    PX_ITEM = 4
}   t_px_type;

typedef struct s_px
{
    uint32_t    color;
    float         depth;
    t_px_type   type;
	int			id;
}   t_px;

typedef struct s_f_img
{
    t_px    *pixels;
    t_img   *img;
    int     width;
    int     height;
}   t_f_img;

typedef struct s_data
{
	t_map	*map;
	t_txt	*txt;
	t_win	*win;
	t_img	*ceiling;

	t_f_img	*render_gmp;
	t_page_id	current_pg;
	t_button *current_buttons;
	int		game_on;
	int		in_game;
	int		slider_button1;
	t_mob 	*mob;
	int		mob_count;
	t_raycast *raycast_f;
	int		slider_button2;
	int		*slider_button;
	t_mouse	mouse;
	int		hud_key_pressed;
	int		pos_y_hud;
	int timer;
	int		win_op;
	int		tilt;
	int		door_state;
	float	offset_door_ratio;
	int		scale;
	int		fps_cap;
	float	fov;
	int player_hp;
	int		res_x;
	t_pl	player;
	int		shift_is_press;
	int		shot1;
	int		shot2;
	int		w_is_press;
	int		s_is_press;
	int		a_is_press;
	int		d_is_press;
	int		p_is_press;
	int 	o_is_press;
	int		res_y;
	int		map_w;
	int		map_h;
}	t_data;
#else

typedef struct s_data
{
	t_map *map;
	t_win *win;
	int		res_x;
	int		res_y;
	t_pl	player;
	float		fov;
	int		w_is_press;
	int		s_is_press;
	int		a_is_press;
	int		d_is_press;
}	t_data;
#endif
// // Table de noms de textures
// static const char *texture_names[] = 
// {
//     "HUD_placeholed",
// 	"mettre_nom_txt_ici",
//     NULL // marqueur de fin
// };
 void	draw_mini_map_centered(t_data *data, int radius, int thickness, int pos[2]);
void	draw_circle(t_data *img, int i[4], int color);
void free_data_mand(t_data *data);
void print_image_window_simple(t_data *data, const char *path, int x, int y);
void	upscale(t_data *data);
void mlx_game_loop(t_data *data);
void get_player_original_pos(t_data  *data);
void	mouv_player(t_data *data);
void 	is_player_hit(t_data *data);
void	draw_rect_fill(t_data *data, int pos[2], int scale[2], int color);
void resize_window(t_data *data, int resx, int resy);
char	*ft_strcpy(char *dest, char *src);
void	init_line_params(t_line *line, float x1, float y1);
int handle_mouse_move(int x, int y, t_data *data);
void	print_map(char **map);
int handle_mouse_click(int button, int x, int y, t_data *data);
int	ft_strcmp(char *s1, char *s2);
// void highlight_button(t_data *data, const char *img_name, int pos_x, int pos_y);
char	**getmap(int fd);
int	name_checker(char *str);
char	**ft_realloc(char **map, int size);
float	normalize_angle(float angle);
int handle_mouse_release(int button, int x, int y, t_data *data);
int handle_mouse_press(int button, int x, int y, t_data *data);
void draw_ceiling(t_data *data, int x, int y_end, t_img *ceiling);
void	free_tab(char **map);
float get_wall_x_coord(float dist_h, float dist_v,
						float hit_x, float hit_y, float ra);
t_txt *find_wall_txt(t_data *data, float dist_h, float dist_v, 
							 float ra, float rx_h, float ry_h, 
							 float rx_v, float ry_v);
char	get_player_pos(char **map, int *x, int *y);
void	free_textures(t_data *data, t_txt *textures);
int get_texture_x(t_img *img, float wall_x);
void shooting(t_data *data);
void	copy_texture_to_img(t_img *src, t_img *dst, int pos_x, int pos_y);
void clear_and_exit(t_data *data);
void   render_depth(t_f_img *image);
void	draw_floor(t_data *data, int x, int y_start);
void	reparse(char **map);
uint32_t	depth_render(uint32_t color, int ray_length);
void	draw_rect(t_data *data, int pos[2], int scale[2], int color);
void draw_door_column(t_data *data, int value[5], t_img *img, float depth);
int		check_invalid(char **map);
uint32_t	get_pixel(t_img *img, int x, int y);
void draw_ceiling_to_screen(t_data *data);
int		name_checker(char *str);
char **generate_map(int map_w, int map_h);
// char **generate_map(int level, int *out_map_w, int *out_map_h);
int is_mob(t_data *data, int mx, int my);
void clean_map(char **map, int map_w, int map_h);
void	free_textures_mand(t_txt *textures);
void	draw_ceiling_img(t_data *data);
void draw_ceiling_to_screen(t_data *data);
void draw_ceiling(t_data *data, int x, int y_end, t_img *ceiling);
void	free_map_content(t_data *data, t_map *map);
void	free_map_struct(t_data *data, t_map *map);
void	clean_exit_mand(t_data *data);
void setup_player_exit(char **map, int map_w, int map_h);
void print_map(char **map);
void draw_rays(t_data *data, int offset_x, int offset_y);
void	mouv_player(t_data *data);
void	draw_game_mode(t_data	*data);
void draw_mobs(t_data *data);
char	**allocate_clone(char **map);
char	**clone_map(char **map);
void free_map(char **map);
void	new_map_random(t_data *data);
void	check_map_ff(t_data *data, t_map *map);
void	mob_path(t_data *data);
char **make_map(t_data *data);
void draw_mini_map(t_data *data, int offset_x, int offset_y);
void	draw_home_page(t_data *data);
void	draw_background_mand(t_data *data);
void knockback(t_data *data);
void cast_horizontal_mob_ray(t_data *data, float *rx, float *ry, float angle);
void cast_vertical_mob_ray(t_data *data, float *rx, float *ry, float angle);
int	is_valid_map(t_data *data);
int	check_arg_and_open(int ac, char **av);
int	is_wall_hit(t_data *data, int mx, int my);
void	draw_setting(t_data *data);
// char **make_map(t_data *data, int level);
void	create_windows(t_win *win,t_data *data);
void	cleanup_data(t_data *data);
float calculate_mob_distance(t_data *data, int i);
void	init_textures_mand(t_data *data);
int	flood_fill_element(char **map, int x, int y, char element);
t_data	*init_data(void);
void highlight_button(t_data *data, t_button *b);
int clean_and_exit(t_data *data, int exit_code);
void	put_string_to_img(t_data *data, int pos[2], uint32_t color, char *str);
int handle_close(void *param);
int handle_key(int keycode, void *param);
char	*ft_sprintf(const char *format, ...);
t_txt *init_textures(t_data *data);
void go_play_menu(t_data *data);
void	cast_vertical_ray(t_data *data, float *rx, float *ry, float angle);
void	cast_horizontal_ray(t_data *data, float *rx, float *ry, float angle);
void go_setting_menu(t_data *data);
int is_door_hit(t_data *data, int mx, int my);
void	print_texture_set(t_txt *txt);
void	cast_horizontal_ray(t_data *data, float *rx, float *ry, float angle);
void	cast_vertical_ray(t_data *data, float *rx, float *ry, float angle);
void draw_map(t_win *win, char **map, int offset_x, int offset_y);
int	is_too_close(t_room *rooms, int room_count, int x, int y, int w, int h);
int is_too_close_y(t_room *rooms, int room_count, int y, int h);
int	is_too_close_x(t_room *rooms, int room_count, int x, int w);
void draw_wall_column(t_data *data, int value[5], t_img *img, float depth);
void	cast_horizontal_door_ray(t_data *data, float *rx, float *ry, float angle);
void	put_pixel(t_img *img, int x, int y, uint32_t color);
void	cast_vertical_door_ray(t_data *data, float *rx, float *ry, float angle);
t_txt *find_texture(t_txt *textures, const char *name);
void get_img_size(char **element, int size[2]);
void draw_to_img(t_data *data, const char *txt_name, int pos_x, int pos_y);
int render_frame(t_data *data);
t_map	*parse_file(int fd);
void draw_rays_3d(t_data *data, int offset_x, int offset_y);
//FREE AND CLEAN
void	free_map(char **map);
void	clean_windows(t_win *win);
void	clean_data(t_data *data);
int	is_player(char c);
int	get_color_map(char c);
void	draw_tile(t_win *win, int x, int y, int color);
void	draw_player(t_data *data, int offset_x, int offset_y);

void	draw_walls_3d(t_data *data);
void draw_rays_3d_bonus(t_data *data, int offset_x, int offset_y);
void	clean_exit_mand(t_data *data);
void mlx_game_loop(t_data *data);
//REPARSE
void	reparse_west(char **map, int px);
void	reparse_north(char **map, int py);
void	reparse_south(char **map, int py);
void	reparse_east(char **map, int px);

//SETTING MENU
void	resize_640(t_data *data);
void	resize_1280(t_data *data);
void	resize_1920(t_data *data);
void	draw_setting(t_data *data);
void 	draw_background_mand(t_data *data);
//GAME SELECTOR MENU
void	play_mainmenu(t_data *data);
void	play_mandatory(t_data *data);
void	play_endless_mode(t_data *data);
void	play_survivor_mode(t_data *data);
void	back_to_main(t_data *data);

//HANDLEKEY AND HANDLEMOUSE
int handle_key_release(int keycode, t_data *data);
int handle_key_press(int keycode, t_data *data);
void handle_key_game(t_data *data);

//RENDER GAMEPLAY
void	render_gameplay_full(t_data *data);

//HANDLE PAUSE MENU
void	draw_pause_menu(t_data *data);
void darken_image(t_img *img, float factor);
#endif