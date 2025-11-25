/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:02:43 by hugz              #+#    #+#             */
/*   Updated: 2025/11/24 16:04:13 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS 

void animate_door(t_data *data)
{
    static int timer = 0;
    int y;
	int x;

    if (data->door_state == 1) 
    {
        if (data->offset_door_ratio < 1.0)
            data->offset_door_ratio += 0.1;
        timer++;
        if (timer >= 75 && 
            check_open_door_collision(data, data->player.px, data->player.py, 0.4) != 1)
        {
            data->door_state = 0;
            timer = 0;
        }
    }
	else if (data->door_state == 0)
	{
		if (data->offset_door_ratio > 0.0)
		{
			data->offset_door_ratio -= 0.1;
		}
		else
		{
			for (y = 0; y < data->map->height; y++)
			{
				for (x = 0; x < data->map->width; x++)
				{
					if (data->map->map[y][x] == 'L')
						data->map->map[y][x] = 'D';
				}
			}
		}
		timer = 0;
	}

}

#endif