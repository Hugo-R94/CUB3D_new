/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:11:19 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 14:14:03 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

void	update_head_bob(t_data *data, int *up)
{
	if (*up == 1)
	{
		if (data->player.pl_height <= 7)
			data->player.pl_height += (2 * data->player.mouv_speed * 10);
		else
			*up = 0;
	}
	else
	{
		if (data->player.pl_height >= -7)
			data->player.pl_height -= (2 * data->player.mouv_speed * 10);
		else
			*up = 1;
	}
}

void	mouv_player(t_data *data)
{
	if (!data)
		return ;
	if (data->current_pg == GAME_PG)
		handle_movement(data);
}

static void	get_facing_coords(t_data *data, int *x, int *y)
{
	double	angle;

	*x = data->player.px;
	*y = data->player.py;
	angle = fmod(data->player.pa, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle >= 7 * M_PI / 4 || angle < M_PI / 4)
		(*x)++;
	else if (angle >= M_PI / 4 && angle < 3 * M_PI / 4)
		(*y)++;
	else if (angle >= 3 * M_PI / 4 && angle < 5 * M_PI / 4)
		(*x)--;
	else
		(*y)--;
}

static void	toggle_door(t_data *data, int x, int y)
{
	if (data->map->map[y][x] == 'D')
	{
		data->door_state = 1;
		data->map->map[y][x] = 'L';
	}
	else
	{
		data->door_state = 0;
		data->map->map[y][x] = 'D';
	}
}

void	action_key(t_data *data)
{
	int	next_x;
	int	next_y;

	if (!data || !data->map || !data->map->map)
		return ;
	get_facing_coords(data, &next_x, &next_y);
	if (next_y >= 0 && data->map->map[next_y]
		&& next_x >= 0 && data->map->map[next_y][next_x])
	{
		if (data->map->map[next_y][next_x] == 'D'
			|| data->map->map[next_y][next_x] == 'L')
			toggle_door(data, next_x, next_y);
	}
}

#endif