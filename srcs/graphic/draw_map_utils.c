/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:24:09 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/28 16:24:43 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_player(char c)
{
	if (c == 'S' || c == 'N' || c == 'E' || c == 'O')
		return (1);
	return (0);
}

int	get_color_map(char c)
{
	if (c == '0' || c == 'D' || c == 'M' || is_player(c))
		return (0x0000FF);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'O')
		return (-1);
	else if (c == 'X')
		return (0xFFFF00);
	else
		return (0x000000);
}

// Dessine un carré de TILE_SIZE x TILE_SIZE à la position (x, y)
void	draw_tile(t_win *win, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < TILE_SIZE)
	{
		j = -1;
		while (++j < TILE_SIZE)
		{
			put_pixel(win->img, x + j, y + i, color);
		}
	}
}

void	draw_player(t_data *data, int offset_x, int offset_y)
{
	int	center_x;
	int	center_y;
	int	color;
	int	idx[2];

	color = 0xFF0000;
	center_x = offset_x + data->player.px * TILE_SIZE;
	center_y = offset_y + data->player.py * TILE_SIZE;
	idx[0] = -(TILE_SIZE / 5) - 1;
	while (++idx[0] <= TILE_SIZE / 5)
	{
		idx[1] = -(TILE_SIZE / 5) - 1;
		while (++idx[1] <= TILE_SIZE / 5)
		{
			put_pixel(data->win->img, center_x + idx[1],
				center_y + idx[0], color);
		}
	}
	draw_rays_3d(data, offset_x, offset_y);
}
