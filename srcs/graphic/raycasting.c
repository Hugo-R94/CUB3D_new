/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:53:14 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/27 14:05:05 by hugz             ###   ########.fr       */
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
