/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:40:37 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 13:09:45 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

void	play_mandatory(t_data *data)
{
	new_map_random(data);
	data->player.is_alive = 1;
	data->current_pg = GAME_PG;
}

void	do_nothing(t_data *data)
{
	if (data)
		return ;
	else
		return ;
}

void	play_endless_mode(t_data *data)
{
	new_map_random(data);
	data->player.is_alive = 1;
	data->current_pg = GAME_PG;
}

void	fill_survivor_map(t_data *data, int size)
{
	int	y;
	int	x;

	y = -1;
	while (++y < size)
	{
		data->map->map[y] = malloc(sizeof(char) * (size + 1));
		if (!data->map->map[y])
			return ;
		x = -1;
		while (++x < size)
		{
			if (x == 0 || x == size - 1 || y == 0 || y == size - 1)
				data->map->map[y][x] = '1';
			else if (x == size / 2 && y == size / 2)
				data->map->map[y][x] = 'S';
			else
				data->map->map[y][x] = '0';
		}
		data->map->map[y][size] = '\0';
	}
	data->map->map[size] = NULL;
}

void	survivor_map(t_data *data)
{
	int	size;

	size = 25;
	data->map->height = size;
	data->map->width = size;
	data->map->map = malloc(sizeof(char *) * (size + 1));
	if (!data->map->map)
		return ;
	fill_survivor_map(data, size);
}

#endif