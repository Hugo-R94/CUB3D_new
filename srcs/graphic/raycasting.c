/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:53:14 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/26 13:56:46 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

static void	draw_line_pixels(t_win *win, t_line *line, int color)
{
	int	i;

	i = 0;
	while (i < line->steps)
	{
		put_pixel(win->img, (int)line->x, (int)line->y, color);
		line->x += line->x_inc;
		line->y += line->y_inc;
		i++;
	}
}

void	draw_line(t_win *win, float x[2], float y[2], int color)
{
	t_line	line;

	line.dx = x[1] - x[0];
	line.dy = y[1] - y[0];
	init_line_params(&line, x[0], y[0]);
	draw_line_pixels(win, &line, color);
	put_pixel(win->img, (int)x[1], (int)y[1], 0xFF0000);
}

static void	cast_single_ray(t_data *data, t_raycast *rc, int i)
{
	float	dist_h;
	float	dist_v;

	rc->ra = data->player.pa - ((data->fov) / 2)
		+ ((data->fov) * i) / data->res_x;
	rc->ra = normalize_angle(rc->ra);
	cast_horizontal_ray(data, &rc->rx_h, &rc->ry_h, rc->ra);
	cast_vertical_ray(data, &rc->rx_v, &rc->ry_v, rc->ra);
	dist_h = sqrtf(powf(rc->rx_h - data->player.px, 2)
			+ powf(rc->ry_h - data->player.py, 2));
	dist_v = sqrtf(powf(rc->rx_v - data->player.px, 2)
			+ powf(rc->ry_v - data->player.py, 2));
	if (dist_h < dist_v)
	{
		rc->rx_final = rc->rx_h;
		rc->ry_final = rc->ry_h;
	}
	else
	{
		rc->rx_final = rc->rx_v;
		rc->ry_final = rc->ry_v;
	}
}

void	draw_ray_line(t_data *data, t_raycast *rc, int offset_x, int offset_y)
{
	float	x[2];
	float	y[2];

	x[0] = offset_x + data->player.px * TILE_SIZE;
	x[1] = offset_x + rc->rx_final * TILE_SIZE;
	y[0] = offset_y + data->player.py * TILE_SIZE;
	y[1] = offset_y + rc->ry_final * TILE_SIZE;
	draw_line(data->win, x, y, 0x00FF00);
}
#ifdef BONUS 

void	draw_rays_3d(t_data *data, int offset_x, int offset_y)
{
	int		i;
	float	x[2];
	float	y[2];

	i = 0;
	while (i < data->res_x)
	{
		x[0] = offset_x + data->player.px * TILE_SIZE;
		y[0] = offset_y + data->player.py * TILE_SIZE;
		x[1] = offset_x + data->raycast_f[i].rx_final * TILE_SIZE;
		y[1] = offset_y + data->raycast_f[i].ry_final * TILE_SIZE;
		draw_line(data->win, x, y, 0x00FF00);
		i++;
	}
}

void	draw_ray_line_bonus(t_data *data, t_raycast *rc,
	int offset_x, int offset_y)
{
	float	x[2];
	float	y[2];

	x[0] = offset_x + data->player.px * TILE_SIZE;
	x[1] = offset_x + rc->rx_final * TILE_SIZE;
	y[0] = offset_y + data->player.py * TILE_SIZE;
	y[1] = offset_y + rc->ry_final * TILE_SIZE;
	draw_line(data->win, x, y, 0x00FF00);
}

void	draw_rays_3d_bonus(t_data *data, int offset_x, int offset_y)
{
	int	i;

	if (!is_valid_map(data) || !data->raycast_f)
		return ;
	i = 0;
	while (i < data->res_x)
	{
		draw_ray_line_bonus(data, &data->raycast_f[i], offset_x, offset_y);
		i++;
	}
}

#endif