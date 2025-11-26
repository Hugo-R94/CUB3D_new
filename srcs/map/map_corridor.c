/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_corridor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:46:48 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 18:57:35 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

void	carve_tile(char **map, int pos[2], int map_w, int map_h)
{
	if (pos[0] <= 0 || pos[1] <= 0
		|| pos[0] >= map_w - 1 || pos[1] >= map_h - 1)
		return ;
	if (map[pos[1]][pos[0]] == '1' || map[pos[1]][pos[0]] == ' ')
		map[pos[1]][pos[0]] = '0';
}

void	carve_horizontal(char **map, int *coords, int params[2])
{
	int	door;

	door = 0;
	while (coords[0] != coords[2])
	{
		if (coords[0] < coords[2])
			coords[0] += 1;
		else
			coords[0] -= 1;
		if (!door && map[coords[1]][coords[0]] == '1')
		{
			map[coords[1]][coords[0]] = 'D';
			door = 1;
		}
		else
			carve_tile(map, (int []){coords[0],
				coords[1]}, params[0], params[1]);
	}
}

void	carve_vertical(char **map, int *coords, int params[2])
{
	while (coords[1] != coords[3])
	{
		if (coords[1] < coords[3])
			coords[1] += 1;
		else
			coords[1] -= 1;
		carve_tile(map, (int []){coords[0], coords[1]}, params[0], params[1]);
	}
}

void	create_corridor(char **map, t_room r1, t_room r2, int params[2])
{
	int	coords[4];

	coords[0] = r1.cx;
	coords[1] = r1.cy;
	coords[2] = r2.cx;
	coords[3] = r2.cy;
	carve_horizontal(map, coords, params);
	carve_vertical(map, coords, params);
}

#endif