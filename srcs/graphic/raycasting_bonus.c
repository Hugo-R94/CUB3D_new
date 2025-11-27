/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:04:26 by hugz              #+#    #+#             */
/*   Updated: 2025/11/27 14:05:08 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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