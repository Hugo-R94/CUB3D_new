/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:44:23 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 18:56:20 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

int	is_valid_pos(int x, int y, int map_w, int map_h)
{
	return (x >= 0 && x < map_w && y >= 0 && y < map_h);
}

void	fill_map_row(char *row, int map_w)
{
	int	x;

	x = -1;
	while (++x < map_w)
		row[x] = '1';
	row[map_w] = '\0';
}

char	**alloc_map(int map_w, int map_h)
{
	char	**map;
	int		y;

	map = calloc(map_h + 1, sizeof(char *));
	y = -1;
	while (++y < map_h)
	{
		map[y] = calloc(map_w + 1, sizeof(char));
		fill_map_row(map[y], map_w);
	}
	map[map_h] = NULL;
	return (map);
}

int	is_valid(int pos[2], char **map, int **visited, int params[2])
{
	return (pos[0] >= 0 && pos[0] < params[0]
		&& pos[1] >= 0 && pos[1] < params[1]
		&& (map[pos[1]][pos[0]] == '0' || map[pos[1]][pos[0]] == 'D'
		|| map[pos[1]][pos[0]] == 'E')
		&& visited[pos[1]][pos[0]] == -1);
}

int	**init_distance_grid(int map_w, int map_h)
{
	int	**dist;
	int	y;
	int	x;

	dist = malloc(sizeof(int *) * map_h);
	y = -1;
	while (++y < map_h)
	{
		dist[y] = malloc(sizeof(int) * map_w);
		x = -1;
		while (++x < map_w)
			dist[y][x] = -1;
	}
	return (dist);
}

#endif