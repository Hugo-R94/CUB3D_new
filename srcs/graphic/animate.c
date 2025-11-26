/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:02:43 by hugz              #+#    #+#             */
/*   Updated: 2025/11/26 10:43:31 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS 

static void	update_door_open(t_data *data, int *timer)
{
	if (data->offset_door_ratio < 1.0)
		data->offset_door_ratio += 0.1;
	(*timer)++;
	if (*timer >= 75
		&& check_open_door_collision(data, data->player.px,
			data->player.py, 0.4) != 1)
	{
		data->door_state = 0;
		*timer = 0;
	}
}

static void	update_door_close(t_data *data, int *timer)
{
	int	y;
	int	x;

	if (data->offset_door_ratio > 0.0)
		data->offset_door_ratio -= 0.1;
	else
	{
		y = 0;
		while (y < data->map->height)
		{
			x = 0;
			while (x < data->map->width)
			{
				if (data->map->map[y][x] == 'L')
					data->map->map[y][x] = 'D';
				x++;
			}
			y++;
		}
	}
	*timer = 0;
}

void	animate_door(t_data *data)
{
	static int	timer = 0;

	if (data->door_state == 1)
		update_door_open(data, &timer);
	else if (data->door_state == 0)
		update_door_close(data, &timer);
}

#endif