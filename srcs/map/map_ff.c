/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:45:00 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 18:55:04 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

void	init_directions(int dirs[4][2])
{
	dirs[0][0] = 1;
	dirs[0][1] = 0;
	dirs[1][0] = -1;
	dirs[1][1] = 0;
	dirs[2][0] = 0;
	dirs[2][1] = 1;
	dirs[3][0] = 0;
	dirs[3][1] = -1;
}

void	process_neighbors(char **map, int **dist, t_point *queue, int params[4])
{
	int		dirs[4][2];
	t_point	p;
	int		i;
	int		coords[2];

	init_directions(dirs);
	p = queue[params[2]++];
	i = -1;
	while (++i < 4)
	{
		coords[0] = p.x + dirs[i][0];
		coords[1] = p.y + dirs[i][1];
		if (is_valid(coords, map, dist, (int []){params[0], params[1]}))
		{
			dist[coords[1]][coords[0]] = dist[p.y][p.x] + 1;
			queue[params[3]++] = (t_point){coords[0], coords[1]};
		}
	}
}

void	flood_fill(char **map, int **dist, t_point *queue, int params[4])
{
	while (params[2] < params[3])
		process_neighbors(map, dist, queue, params);
}

int	find_player_pos(char **map, int map_w, int map_h, int *pos)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map_h)
	{
		x = -1;
		while (++x < map_w)
		{
			if (map[y][x] == '0')
			{
				map[y][x] = 'S';
				pos[0] = x;
				pos[1] = y;
				return (1);
			}
		}
	}
	return (0);
}

void	find_farthest_point(int **dist, int map_w, int map_h, int *exit)
{
	int	max_dist;
	int	x;
	int	y;

	max_dist = -1;
	y = -1;
	while (++y < map_h)
	{
		x = -1;
		while (++x < map_w)
		{
			if (dist[y][x] > max_dist)
			{
				max_dist = dist[y][x];
				exit[0] = x;
				exit[1] = y;
			}
		}
	}
}

#endif