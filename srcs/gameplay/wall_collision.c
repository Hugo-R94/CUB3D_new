/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:24:08 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 12:24:39 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

int	is_wall(t_data *data, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map->width || y >= data->map->height)
		return (1);
	if (data->map->map[y][x] == '1' || data->map->map[y][x] == '2'
		|| data->map->map[y][x] == '3' || data->map->map[y][x] == 'D')
		return (1);
	return (0);
}

int	check_wall_collision(t_data *data, float x, float y, float r)
{
	if (is_wall(data, (int)(x - r), (int)(y - r)) == 1)
		return (1);
	if (is_wall(data, (int)(x + r), (int)(y - r)) == 1)
		return (1);
	if (is_wall(data, (int)(x - r), (int)(y + r)) == 1)
		return (1);
	if (is_wall(data, (int)(x + r), (int)(y + r)) == 1)
		return (1);
	return (0);
}

int	check_collision(t_data *data, float pos[2], float r, char c)
{
	if (data->map->map[(int)(pos[1] - r)][(int)(pos[0] - r)] == c)
		return (1);
	if (data->map->map[(int)(pos[1] - r)][(int)(pos[0] + r)] == c)
		return (1);
	if (data->map->map[(int)(pos[1] + r)][(int)(pos[0] - r)] == c)
		return (1);
	if (data->map->map[(int)(pos[1] + r)][(int)(pos[0] + r)] == c)
		return (1);
	return (0);
}

int	check_open_door_collision(t_data *data, float x, float y, float r)
{
	if (data->map->map[(int)y][(int)x] == 'L')
		return (1);
	if (data->map->map[(int)(y - r)][(int)(x - r)] == 'D')
		return (1);
	if (data->map->map[(int)(y - r)][(int)(x + r)] == 'D')
		return (1);
	if (data->map->map[(int)(y + r)][(int)(x - r)] == 'D')
		return (1);
	if (data->map->map[(int)(y + r)][(int)(x + r)] == 'D')
		return (1);
	return (0);
}

#endif