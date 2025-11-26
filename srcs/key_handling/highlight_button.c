/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   highlight_button.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:30:55 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/25 14:29:55 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS

void	highlight_button(t_data *data, t_button *b)
{
	int	border;
	int	x;
	int	y;

	border = 3;
	x = 0;
	y = 0;
	y = b->y - border - 1;
	while (++y <= b->y + b->height + border)
	{
		x = b->x - border - 1;
		while (++x <= b->x + b->width + border)
		{
			if (x < b->x || x >= b->x + b->width
				|| y < b->y || y >= b->y + b->height)
			{
				if (x >= 0 && y >= 0
					&& x < data->win->img->width && y < data->win->img->height)
				{
					put_pixel(data->win->img, x, y, 0xFF0000);
				}
			}
		}
	}
}
#endif