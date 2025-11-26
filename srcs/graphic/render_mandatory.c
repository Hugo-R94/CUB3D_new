/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mandatory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:01:42 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/26 18:44:27 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifndef BONUS

static t_txt	*get_horizontal_texture(t_data *data, float ra)
{
	if (sin(ra) > 0)
		return (&data->map->textures[1]);
	else
		return (&data->map->textures[0]);
}

static t_txt	*get_vertical_texture(t_data *data, float ra)
{
	if (cos(ra) > 0)
		return (&data->map->textures[2]);
	else
		return (&data->map->textures[3]);
}

t_txt	*find_wall_txt(t_data *data, float dist_h, float dist_v, float ra)
{
	if (dist_h < dist_v)
		return (get_horizontal_texture(data, ra));
	else
		return (get_vertical_texture(data, ra));
}

static float	calculate_distance(float x1, float y1, float x2, float y2)
{
	float	dx;
	float	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrtf(dx * dx + dy * dy));
}

static void	get_distances(t_data *data, float ra, float *dist_h, float *dist_v)
{
	float	rx_h;
	float	ry_h;
	float	rx_v;
	float	ry_v;

	cast_horizontal_ray(data, &rx_h, &ry_h, ra);
	cast_vertical_ray(data, &rx_v, &ry_v, ra);
	*dist_h = calculate_distance(data->player.px, data->player.py, rx_h, ry_h);
	*dist_v = calculate_distance(data->player.px, data->player.py, rx_v, ry_v);
}

static float	get_corrected_distance(t_data *data, float ra, float dist)
{
	float	dist_final;

	dist_final = dist;
	dist_final *= cos(data->player.pa - ra);
	if (dist_final < 0.1f)
		dist_final = 0.1f;
	return (dist_final);
}

static int	calculate_line_height(t_data *data, float dist_final, int *full_h)
{
	float	plane_dist;
	int		line_h;

	plane_dist = (data->res_x / 2.0f) / tan(data->fov / 2.0f);
	line_h = (int)(plane_dist / dist_final);
	*full_h = line_h;
	if (line_h > data->res_y)
		line_h = data->res_y;
	return (line_h);
}

static float	get_horizontal_wall_x(float hit_x, float ra)
{
	float	wall_x;

	wall_x = hit_x - floor(hit_x);
	if (sin(ra) > 0)
		wall_x = 1.0f - wall_x;
	return (wall_x);
}

static float	get_vertical_wall_x(float hit_y, float ra)
{
	float	wall_x;

	wall_x = hit_y - floor(hit_y);
	if (cos(ra) < 0)
		wall_x = 1.0f - wall_x;
	return (wall_x);
}

int	get_texture_x(t_img *img, float wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * img->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= img->width)
		tex_x = img->width - 1;
	return (tex_x);
}

//i[0] = x || i[1] = y || i[2] = tex_x
static void	put_wall_pixel(t_data *data, t_img *img, int i[3], float tex_pos)
{
	int		tex_y;
	int		color;

	tex_y = (int)tex_pos;
	color = get_pixel(img, i[2], tex_y);
	put_pixel(data->win->img, i[0], i[1], color);
}

static void	draw_ceiling(t_data *data, int x, int start_y, int end_y)
{
	int	current_y;

	current_y = start_y;
	while (current_y < end_y)
	{
		put_pixel(data->win->img, x, current_y, data->map->c_color);
		current_y++;
	}
}

static void	draw_floor(t_data *data, int x, int start_y)
{
	int	current_y;

	current_y = start_y;
	while (current_y < data->res_y)
	{
		put_pixel(data->win->img, x, current_y, data->map->f_color);
		current_y++;
	}
}

static int	get_line_offset(t_data *data, int full_line_h)
{
	int	line_off;

	line_off = (data->res_y - full_line_h) / 2;
	return (line_off);
}

static float	get_initial_tex_pos(int line_off, float step)
{
	float	tex_pos;

	if (line_off < 0)
		tex_pos = (-line_off) * step;
	else
		tex_pos = 0.0f;
	return (tex_pos);
}

static int	get_start_y(int line_off)
{
	int	y;

	if (line_off < 0)
		y = 0;
	else
		y = line_off;
	return (y);
}

static int	get_end_y(t_data *data, int line_off, int full_line_h)
{
	int	y_end;

	y_end = line_off + full_line_h;
	if (y_end > data->res_y)
		y_end = data->res_y;
	return (y_end);
}

//int x[2] > x[0] = x, x[1] = tex_x
static void	render_column(t_data *data, t_img *img, int x[2], int full_line_h)
{
	int		line_off;
	int		y;
	int		y_end;
	float	tex_pos;
	float	step;

	step = (float)img->height / full_line_h;
	line_off = get_line_offset(data, full_line_h);
	tex_pos = get_initial_tex_pos(line_off, step);
	y = get_start_y(line_off);
	y_end = get_end_y(data, line_off, full_line_h);
	draw_ceiling(data, x[0], 0, y);
	while (y < y_end)
	{
		put_wall_pixel(data, img, (int []){x[0], y, x[1]}, tex_pos);
		tex_pos += step;
		y++;
	}
	draw_floor(data, x[0], y_end);
}

//dist[0] = dist_h | dist[1] = dist_v | dist[2] = dist_raw
static float	get_wall_x(t_data *data, float dist[3],
	float ra)
{
	float	hit[2];
	float	wall_x;

	hit[0] = data->player.px + dist[2] * cos(ra);
	hit[1] = data->player.py + dist[2] * sin(ra);
	if (dist[0] < dist[1])
		wall_x = get_horizontal_wall_x(hit[0], ra);
	else
		wall_x = get_vertical_wall_x(hit[1], ra);
	return (wall_x);
}

void	draw_wall_column_txt(t_data *data, int x, float ra)
{
	t_txt	*txt;
	int		full_line_h;
	float	wall_x;
	int		tex_x;
	float	dist[4];

	get_distances(data, ra, &dist[0], &dist[1]);
	txt = find_wall_txt(data, dist[0], dist[1], ra);
	dist[2] = fmin(dist[0], dist[1]);
	dist[3] = get_corrected_distance(data, ra, dist[2]);
	calculate_line_height(data, dist[3], &full_line_h);
	wall_x = get_wall_x(data, (float []){dist[0], dist[1], dist[2]}, ra);
	tex_x = get_texture_x(&txt->img, wall_x);
	render_column(data, &txt->img, (int []){x, tex_x}, full_line_h);
}

static void	process_single_ray(t_data *data, int i, float ra)
{
	ra = normalize_angle(ra);
	draw_wall_column_txt(data, i, ra);
}

void	draw_walls_3d(t_data *data)
{
	float	ra;
	int		i;

	if (!data || !data->map || !data->map->map)
		return ;
	i = 0;
	while (i < data->res_x)
	{
		ra = data->player.pa - (data->fov / 2) + (data->fov * i) / data->res_x;
		process_single_ray(data, i, ra);
		i++;
	}
}

#endif