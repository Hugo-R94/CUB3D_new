/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:38:42 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/28 16:00:31 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_background_mand(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->res_y)
	{
		x = -1;
		while (++x < data->res_x)
		{
			if (y < data->res_y / 2)
				put_pixel(data->win->img, x, y, data->map->c_color);
			else
				put_pixel(data->win->img, x, y, data->map->f_color);
		}
	}
}
