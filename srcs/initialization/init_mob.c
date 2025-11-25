/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mob.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:20:38 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 13:19:26 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

int	count_mobs(char **map)
{
	int	y;
	int	x;
	int	mob_count;

	y = 0;
	mob_count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'M' || map[y][x] == 'B')
				mob_count++;
			x++;
		}
		y++;
	}
	return (mob_count);
}

void	init_mob_m(t_mob *mob, int x, int y, int id)
{
	mob->mx = x + 0.5;
	mob->my = y + 0.5;
	mob->hp = 2;
	mob->is_alive = 1;
	mob->sprite = "mob";
	mob->size = 0.7;
	mob->id = id;
	mob->chase = 0;
}

void	init_mob_b(t_mob *mob, int x, int y, int id)
{
	mob->mx = x + 0.5;
	mob->my = y + 0.5;
	mob->hp = 5;
	mob->is_alive = 1;
	mob->sprite = "bos";
	mob->size = 2.5;
	mob->id = id;
	mob->chase = 0;
}

void	fill_mobs(t_data *data, int mob_count)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] == 'M')
				init_mob_m(&data->mob[i++], x, y, i - 1);
			else if (data->map->map[y][x] == 'B')
				init_mob_b(&data->mob[i++], x, y, i - 1);
			x++;
		}
		y++;
	}
	data->mob_count = mob_count;
}

void	init_mob(t_data *data)
{
	int	mob_count;

	if (data->mob)
		free(data->mob);
	mob_count = count_mobs(data->map->map);
	data->mob = calloc(mob_count, sizeof(t_mob));
	if (!data->mob)
		return ;
	fill_mobs(data, mob_count);
}

#endif