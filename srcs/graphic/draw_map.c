/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:08:14 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/26 11:10:31 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <mlx.h>
#include <stdlib.h>
#include <math.h>

void	draw_circle(t_data *data, int i[4], int color)
{
	int	x;
	int	y;
	int	dist_squared;
	int	radius_outer_sq;
	int	radius_inner_sq;

	radius_outer_sq = i[2] * i[2];
	radius_inner_sq = (i[2] - i[3]) * (i[2] - i[3]);
	y = i[1] - i[2] - 1;
	while (++y <= i[1] + i[2])
	{
		x = i[0] - i[2] - 1;
		while (++x <= i[0] + i[2])
		{
			dist_squared = (x - i[0]) * (x - i[0]) + (y - i[1]) * (y - i[1]);
			if (dist_squared <= radius_outer_sq
				&& dist_squared >= radius_inner_sq)
				put_pixel(data->win->img, x, y, color);
		}
	}
}

void	draw_mini_map(t_data *data, int offset_x, int offset_y)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	color;

	if (!data->win || !data->win->mlx || !data->win->win)
	{
		printf("Erreur : t_win non initialisé !\n");
		return ;
	}
	i = -1;
	while (data->map->map[++i])
	{
		j = -1;
		while (data->map->map[i][++j])
		{
			x = offset_x + j * TILE_SIZE;
			y = offset_y + i * TILE_SIZE;
			color = get_color_map(data->map->map[i][j]);
			if (color != 0x00000)
				draw_tile(data->win, x, y, color);
		}
	}
	draw_player(data, offset_x, offset_y);
}

static int	is_tile_visible(int pixel[2], int center[2],
				int radius, int thickness)
{
	int	dist_sq;

	dist_sq = (pixel[0] - center[0]) * (pixel[0] - center[0])
		+ (pixel[1] - center[1]) * (pixel[1] - center[1]);
	return (dist_sq <= radius * radius - (thickness * 125));
}

static void	draw_map_tiles(t_data *data, int center[2], int params[2])
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;
	int	color;

	i = -1;
	while (data->map->map[++i] && i < data->map->height)
	{
		j = -1;
		while (data->map->map[i][++j] && j < data->map->width)
		{
			pixel_x = center[0] + (j * TILE_SIZE
					- data->player.px * TILE_SIZE);
			pixel_y = center[1] + (i * TILE_SIZE
					- data->player.py * TILE_SIZE);
			if (is_tile_visible((int []){pixel_x, pixel_y},
				(int []){center[0], center[1]}, params[0], params[1]))
			{
				color = get_color_map(data->map->map[i][j]);
				if (color != 0x000000)
					draw_tile(data->win, pixel_x, pixel_y, color);
			}
		}
	}
}
#ifdef BONUS 

void	draw_mini_map_centered(t_data *data, int radius, int thickness,
			int pos[2])
{
	int	center[2];
	int	params[2];

	if (!data->win || !data->win->mlx || !data->win->win)
		return ;
	center[0] = pos[0];
	center[1] = pos[1];
	params[0] = radius;
	params[1] = thickness;
	draw_map_tiles(data, center, params);
	draw_circle(data, (int []){center[0], center[1], radius, thickness},
		0xFCA612);
	draw_player(data, center[0] - data->player.px * TILE_SIZE,
		center[1] - data->player.py * TILE_SIZE);
	draw_rays_3d_bonus(data, center[0] - data->player.px * TILE_SIZE,
		center[1] - data->player.py * TILE_SIZE);
}
#endif