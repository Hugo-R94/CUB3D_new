/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:55:39 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/27 11:02:28 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS

static void	cast_rays(t_data *data, t_raycast *raycast)
{
	cast_horizontal_ray(data, &raycast->rx_h, &raycast->ry_h, raycast->ra);
	cast_vertical_ray(data, &raycast->rx_v, &raycast->ry_v, raycast->ra);
}

static void	cast_doors_rays(t_data *data, t_raycast *raycast)
{
	cast_horizontal_door_ray(data, &raycast->rx_h, &raycast->ry_h, raycast->ra);
	cast_vertical_door_ray(data, &raycast->rx_v, &raycast->ry_v, raycast->ra);
}

static void	calculate_distances(t_data *data, t_raycast *raycast,
	float *dist_h, float *dist_v)
{
	*dist_h = sqrtf(powf(raycast->rx_h - data->player.px, 2)
			+ powf(raycast->ry_h - data->player.py, 2));
	*dist_v = sqrtf(powf(raycast->rx_v - data->player.px, 2)
			+ powf(raycast->ry_v - data->player.py, 2));
}

static void	cast_mob_rays(t_data *data, t_raycast *raycast)
{
	cast_horizontal_mob_ray(data, &raycast->rx_h, &raycast->ry_h, raycast->ra);
	cast_vertical_mob_ray(data, &raycast->rx_v, &raycast->ry_v, raycast->ra);
}

//dist[0] = dist_h | dist[1] = dist_v
static void	get_final_distance(t_data *data, float dist[2],
	float ra, float *dist_final)
{
	float	dist_raw;
	int		is_side;

	if (dist[1] < dist[0])
	{
		dist_raw = dist[1];
		is_side = 1;
	}
	else
	{
		dist_raw = dist[0];
		is_side = 0;
	}
	if (data->shift_is_press == 1)
		*dist_final = dist_raw;
	else
		*dist_final = dist_raw * cos(data->player.pa - ra);
	if (*dist_final < 0.1f)
		*dist_final = 0.1f;
}

//line[0] = line_h | line[1] = line_off
static void	calculate_wall_dimensions(t_data *data, float dist_final,
				int *line[2], int factor)
{
	float	plane_dist;
	int		screen_h;
	int		screen_w;

	screen_h = 480;
	screen_w = 640;
	plane_dist = (screen_w / 2.0f) / tan(data->fov / 2.0f);
	*line[0] = (int)(plane_dist / dist_final * factor);
	*line[1] = (screen_h - *line[0]) / 2
		+ data->tilt + data->player.pl_height;
}

static void	get_texture_info(t_data *data, float dist[2],
	t_raycast *raycast, t_txt **txt)
{
	float	hit_x;
	float	hit_y;
	float	wall_x;
	float	dist_raw;

	if (dist[1] < dist[0])
		dist_raw = dist[1];
	else
		dist_raw = dist[0];
	*txt = find_wall_txt(data, dist[0], dist[1], raycast);
	hit_x = data->player.px + dist_raw * cos(raycast->ra);
	hit_y = data->player.py + dist_raw * sin(raycast->ra);
	wall_x = get_wall_x_coord(dist[0], dist[1],
			(float [2]){hit_x, hit_y}, raycast->ra);
	raycast->tex_x = get_texture_x(&(*txt)->img, wall_x);
}

static void	render_column(t_data *data, int value[5],
	t_txt *txt, float dist_final)
{
	draw_ceiling(data, value[0], value[1], data->ceiling);
	draw_wall_column(data, value, &txt->img, dist_final);
	draw_floor(data, value[0], value[3] + value[2]);
}

static void	prepare_mob_column(t_column_info *c, int line_h,
	int line_off, t_img *img)
{
	c->screen_h = 480;
	c->line_h = line_h;
	c->step = (float)img->height / line_h;
	c->tex_pos = 0.0f;
	c->start_y = 0;
	c->end_y = line_h;
	if (line_off < 0)
	{
		c->start_y = -line_off;
		c->tex_pos = c->start_y * c->step;
	}
	if (line_off + line_h > c->screen_h)
		c->end_y = c->screen_h - line_off;
}

/* Fonction helper pour stocker les coordonnées du rayon */
static void	store_ray_coords(t_data *data, int i,
	t_raycast *ray, float dists[2])
{
	if (dists[0] < dists[1])
	{
		data->raycast_f[i].rx = ray->rx_h;
		data->raycast_f[i].ry = ray->ry_h;
		data->raycast_f[i].rx_final = ray->rx_h;
		data->raycast_f[i].ry_final = ray->ry_h;
	}
	else
	{
		data->raycast_f[i].rx = ray->rx_v;
		data->raycast_f[i].ry = ray->ry_v;
		data->raycast_f[i].rx_final = ray->rx_v;
		data->raycast_f[i].ry_final = ray->ry_v;
	}
	data->raycast_f[i].ra = ray->ra;
}

/* Fonction pour calculer et dessiner le mur */
static void	process_wall(t_data *data, int i, float ra, float *dist_final)
{
	t_raycast	raycast;
	float		dists[2];
	int			dims[2];
	t_txt		*txt;

	raycast.ra = ra;
	cast_rays(data, &raycast);
	calculate_distances(data, &raycast, &dists[0], &dists[1]);
	get_final_distance(data, (float []){dists[0], dists[1]}, ra, dist_final);
	calculate_wall_dimensions(data, *dist_final,
		(int *[]){&dims[0], &dims[1]}, 1);
	get_texture_info(data, dists, &raycast, &txt);
	store_ray_coords(data, i, &raycast, dists);
	render_column(data, (int []){i, dims[1], dims[0], dims[1], raycast.tex_x},
		txt, *dist_final);
}

/* Fonction pour ajuster les dimensions de la porte */
static void	adjust_door_dimensions(int *line_h, int *line_off)
{
	int	original_bottom;

	original_bottom = *line_off + *line_h;
	*line_off = original_bottom - *line_h;
}

/* Fonction pour calculer et dessiner la porte */
static void	process_door(t_data *data, int i, float ra, float wall_dist)
{
	t_raycast	door_ray;
	float		dists[3];
	int			dims[2];
	t_txt		*txt;

	door_ray.ra = ra;
	cast_doors_rays(data, &door_ray);
	calculate_distances(data, &door_ray, &dists[0], &dists[1]);
	get_final_distance(data, (float []){dists[0], dists[1]}, ra, &dists[2]);
	if (dists[2] > 0 && dists[2] < wall_dist)
	{
		store_ray_coords(data, i, &door_ray, dists);
		calculate_wall_dimensions(data, dists[2],
			(int *[]){&dims[0], &dims[1]}, 1);
		adjust_door_dimensions(&dims[0], &dims[1]);
		get_texture_info(data, dists, &door_ray, &txt);
		draw_door_column(data, (int []){i, dims[1], dims[0], dims[1],
			door_ray.tex_x}, &txt->img, dists[2]);
	}
}

/* Fonction principale */
static void	process_single_ray(t_data *data, int i, float ra)
{
	float	wall_dist;

	process_wall(data, i, ra, &wall_dist);
	process_door(data, i, ra, wall_dist);
}

void	render_gameplay(t_data *data)
{
	float	ra;
	int		i;

	if (!data || !data->map || !data->map->map)
	{
		printf("la y pas de map\n");
		return ;
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
	draw_mobs(data);
	draw_exit(data);
}
#endif