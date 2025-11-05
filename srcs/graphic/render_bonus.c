/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:55:39 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/04 17:50:15 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define FOV (M_PI / 3)

#ifdef BONUS

static void	cast_rays(t_data *data, t_raycast *raycast)
{
	cast_horizontal_ray(data, &raycast->rx_h,  &raycast->ry_h,  raycast->ra);
	cast_vertical_ray(data,  &raycast->rx_v,  &raycast->ry_v,  raycast->ra);
}
static void	cast_doors_rays(t_data *data, t_raycast *raycast)
{
	cast_horizontal_door_ray(data, &raycast->rx_h,  &raycast->ry_h,  raycast->ra);
	cast_vertical_door_ray(data,  &raycast->rx_v,  &raycast->ry_v,  raycast->ra);
}

static void	calculate_distances(t_data *data, t_raycast *raycast, float *dist_h, float *dist_v)
{
	*dist_h = sqrtf(powf(raycast->rx_h - data->player.px, 2) + powf(raycast->ry_h - data->player.py, 2));
	*dist_v = sqrtf(powf(raycast->rx_v - data->player.px, 2) + powf(raycast->ry_v - data->player.py, 2));
}
// static void calculate_distances_door(t_data *data, t_raycast *raycast, float *dist_h, float *dist_v)
// {
//     float rx_h = raycast->rx_h;
//     float ry_h = raycast->ry_h;
//     float rx_v = raycast->rx_v;
//     float ry_v = raycast->ry_v;
	
//     // Collision horizontale : ajuste seulement Y
//     if (data->player.py > raycast->ry_h)
//         ry_h -= 0.5;  // joueur en dessous → pousse le centre vers le bas
//     else
//         ry_h += 0.5;  // joueur au-dessus → pousse vers le haut

//     // Collision verticale : ajuste seulement X
//     if (data->player.px > raycast->rx_v)
//         rx_v -= 0.5;  // joueur à droite → pousse le centre vers la droite
//     else
//         rx_v += 0.5;  // joueur à gauche → pousse vers la gauche

//     *dist_h = sqrtf(powf(rx_h - data->player.px, 2) + powf(ry_h - data->player.py, 2));
//     *dist_v = sqrtf(powf(rx_v - data->player.px, 2) + powf(ry_v - data->player.py, 2));
// }


static void	get_final_distance(t_data *data, float dist_h, float dist_v, float ra, float *dist_final)
{
	float	dist_raw;
	int		is_side;

	if (dist_v < dist_h)
	{
		dist_raw = dist_v;
		is_side = 1;
	}
	else
	{
		dist_raw = dist_h;
		is_side = 0;
	}
	if (data->shift_is_press == 1 )
		*dist_final = dist_raw;
	else
		*dist_final = dist_raw * cos(data->player.pa - ra);
	if (*dist_final < 0.1f)
		*dist_final = 0.1f;
}



static void	calculate_wall_dimensions(t_data *data, float dist_final, int *line_h, int *line_off)
{
	float	plane_dist;
	int		screen_h;
	int		screen_w;

	screen_h = 480;
	screen_w = 640;
	plane_dist = (screen_w / 2.0f) / tan(data->fov / 2.0f);
	*line_h = (int)(plane_dist / dist_final);
	*line_off = (screen_h - *line_h) / 2 + data->tilt;
}

static void	get_texture_info(t_data *data, float dist[2], t_raycast *raycast, t_txt **txt)
{
	float	hit_x;
	float	hit_y;
	float	wall_x;
	float	dist_raw;

	if (dist[1] < dist[0])
		dist_raw = dist[1];
	else
		dist_raw = dist[0];
	*txt = find_wall_txt(data, dist[0], dist[1], raycast->ra, raycast->rx_h, raycast->ry_h, raycast->rx_v, raycast->ry_v);
	hit_x = data->player.px + dist_raw * cos( raycast->ra);
	hit_y = data->player.py + dist_raw * sin( raycast->ra);
	wall_x = get_wall_x_coord(dist[0], dist[1], hit_x, hit_y,  raycast->ra);
	raycast->tex_x = get_texture_x(&(*txt)->img, wall_x);
}

static void	calculate_vertical_limits(int line_off, int line_h, int *y_ceiling_end, int *y_floor_start)
{
	int	screen_h;

	screen_h = 480;
	*y_ceiling_end = line_off;
	if (*y_ceiling_end < 0)
		*y_ceiling_end = 0;
	*y_floor_start = line_off + line_h;
	if (*y_floor_start > screen_h)
		*y_floor_start = screen_h;
}

static void	render_column(t_data *data, int value[5], t_txt *txt, float dist_final)
{
	draw_ceiling(data, value[0], value[1], data->ceiling);
	draw_wall_column(data,  value, &txt->img, dist_final);
	draw_floor(data,  value[0], value[3] + value[2]);
}


// static void process_single_ray(t_data *data, int i, float ra)
// {
// 	t_raycast   raycast;
// 	t_raycast   door_ray;
// 	float       dist_h;
// 	float       dist_v;
// 	float       door_dist_h;
// 	float       door_dist_v;
	
// 	float       dist_final;
// 	int         line_h;
// 	int         line_off;
	
// 	// ===== RENDU DU MUR =====
// 	raycast.ra = ra;
// 	cast_rays(data, &raycast);
// 	calculate_distances(data, &raycast, &dist_h, &dist_v);
// 	get_final_distance(data, dist_h, dist_v, ra, &dist_final);
// 	calculate_wall_dimensions(data, dist_final, &line_h, &line_off);
	
// 	t_txt *txt;
// 	get_texture_info(data, (float []){dist_h, dist_v}, &raycast, &txt);
	
// 	int y_ceiling_end;
// 	int y_floor_start;
// 	float       dist_final_door;
// 	calculate_vertical_limits(line_off, line_h, &y_ceiling_end, &y_floor_start);
// 	render_column(data, (int []){i, y_ceiling_end, line_h, line_off, raycast.tex_x}, txt, dist_final);
	
// 	cast_doors_rays(data, &door_ray);
// 	calculate_distances(data, &door_ray, &door_dist_h, &door_dist_v);
// 	get_final_distance(data,door_dist_h, door_dist_v, ra, &dist_final_door);
// 	calculate_wall_dimensions(data, dist_final_door, &line_h, &line_off);
// 	get_texture_info(data, (float []){door_dist_h, door_dist_v}, &door_ray, &txt);
// 	if (dist_final_door <= dist_final)
// 		draw_door_column(data,(int []){i, y_ceiling_end, line_h, line_off, raycast.tex_x},find_texture(txt,"door")->img.image,dist_final);
// }

static void process_single_ray(t_data *data, int i, float ra)
{
	t_raycast   raycast;
	t_raycast   door_ray;
	float       dist_h;
	float       dist_v;
	float       dist_final;
	int         line_h;
	int         line_off;
	
	// ===== RENDU DU MUR =====
	raycast.ra = ra;
	cast_rays(data, &raycast);
	calculate_distances(data, &raycast, &dist_h, &dist_v);
	get_final_distance(data, dist_h, dist_v, ra, &dist_final);
	calculate_wall_dimensions(data, dist_final, &line_h, &line_off);
	
	t_txt *txt;
	get_texture_info(data, (float []){dist_h, dist_v}, &raycast, &txt);
	
	int y_ceiling_end;
	int y_floor_start;
	calculate_vertical_limits(line_off, line_h, &y_ceiling_end, &y_floor_start);
	render_column(data, (int []){i, y_ceiling_end, line_h, line_off, raycast.tex_x}, txt, dist_final);
    // ===== RENDU DE LA PORTE =====
    door_ray.ra = ra;
    cast_doors_rays(data, &door_ray);
    
    float door_dist_h;
    float door_dist_v;
    float door_dist_final;
    calculate_distances(data, &door_ray, &door_dist_h, &door_dist_v);
  // Dans process_single_ray, après le calcul des distances de la porte
  	if (door_dist_v < door_dist_h)
	{
		door_dist_final = door_dist_v + 0.5;
	}
	else
	{
		door_dist_final = door_dist_h + 0.5;
	}
	calculate_distances(data, &door_ray, &door_dist_h, &door_dist_v);

	printf("BEFORE fisheye: door_dist_h=%.2f, door_dist_v=%.2f\n", door_dist_h, door_dist_v);

	get_final_distance(data, door_dist_h, door_dist_v, ra, &door_dist_final);

	printf("AFTER fisheye: door_dist_final=%.2f, ra=%.2f, pa=%.2f, cos(pa-ra)=%.2f\n", 
       door_dist_final, ra, data->player.pa, cos(data->player.pa - ra));
    if (door_dist_final > 0 && door_dist_final < dist_final)
    {
        int door_line_h;
        int door_line_off;
        t_txt *img;

        img = find_texture(txt, "door");
        calculate_wall_dimensions(data, door_dist_final, &door_line_h, &door_line_off);
        get_texture_info(data, (float []){door_dist_h, door_dist_v}, &door_ray, &txt);
        calculate_vertical_limits(door_line_off, door_line_h, &y_ceiling_end, &y_floor_start); 
        draw_door_column(data, (int []){i, y_ceiling_end, door_line_h, door_line_off, door_ray.tex_x}, &img->img, door_dist_final);
    }
}

void	draw_walls_3d(t_data *data)
{
	float	ra;
	int		i;

	if (!data || !data->map || !data->map->map)
	{
		printf("la y pas de map\n");
		return;
	}
	i = 0;
	while (i < 640)
	{
		ra = data->player.pa - (data->fov / 2) + (data->fov * i) / 640;
		while (ra < 0)
			ra += 2 * M_PI;
		while (ra >= 2 * M_PI)
			ra -= 2 * M_PI;
		process_single_ray(data, i, ra);
		i++;
	}
}

#endif