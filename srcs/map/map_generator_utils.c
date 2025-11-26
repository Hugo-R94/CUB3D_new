/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:22:15 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/25 15:57:18 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS

int	has_door_in_line_or_column(char **map, int x, int y)
{
	int	j;
	int	i;

	i = -1;
	j = -1;
	while (map[++j])
		if (map[j][x] == 'D')
			return (1);
	while (map[y][++i])
		if (map[y][i] == 'D')
			return (1);
	return (0);
}

static int	should_keep_wall(char **map, int pos[2], int map_w, int map_h)
{
	int	dy;
	int	dx;
	int	ny;
	int	nx;

	dy = -2;
	while (++dy <= 1)
	{
		dx = -2;
		while (++dx <= 1)
		{
			if (dx == 0 && dy == 0)
				continue ;
			ny = pos[0] + dy;
			nx = pos[1] + dx;
			if (ny < 0 || ny >= map_h || nx < 0 || nx >= map_w)
				continue ;
			if (map[ny][nx] == '0' || map[ny][nx] == 'D')
				return (1);
		}
	}
	return (0);
}

void	clean_map(char **map, int map_w, int map_h)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map_h)
	{
		x = -1;
		while (++x < map_w)
		{
			if (map[y][x] == '1' && !should_keep_wall(map,
				(int []){y, x}, map_w, map_h))
				map[y][x] = ' ';
		}
	}
}

int	is_potential_door(char **m, int x, int y)
{
	int	cond1;
	int	cond2;

	if (x <= 0 || y <= 0 || !m[y + 1] || !m[y][x + 1])
		return (0);
	cond1 = (m[y + 1][x] == '1'
			&& m[y - 1][x] == '1'
			&& m[y][x + 1] == '0'
			&& m[y][x - 1] == '0');
	cond2 = (m[y + 1][x] == '0'
			&& m[y - 1][x] == '0'
			&& m[y][x + 1] == '1'
			&& m[y][x - 1] == '1');
	return (cond1 || cond2);
}

void	setup_doors(char **m)
{
	int	x;
	int	y;

	y = 0;
	while (m[y])
	{
		x = 0;
		while (m[y][x])
		{
			if (m[y][x] == '0'
				&& is_potential_door(m, x, y)
				&& !has_door_in_line_or_column(m, x, y))
				m[y][x] = 'D';
			x++;
		}
		y++;
	}
}
#endif