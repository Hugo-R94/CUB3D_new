/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:15:37 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/29 12:24:25 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_player(t_map *map)
{
	int	y;
	int	x;
	int	player_count;

	player_count = 0;
	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S'
				|| map->map[y][x] == 'E' || map->map[y][x] == 'W')
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count != 1)
	{
		ft_printf("There must be only one player.\n");
		return (1);
	}
	return (0);
}

char	get_player_pos(char **map, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				*x = j;
				*y = i;
				return (map[i][j]);
			}
			j++;
		}
		i++;
	}
	return ('\0');
}

static void	check_map_floods(t_data *data, t_map *map, int px, int py)
{
	char	**clone;
	char	fill_chars[3];
	int		i;

	i = -1;
	fill_chars[0] = ' ';
	fill_chars[1] = '\n';
	fill_chars[2] = '\0';
	while (++i < 3)
	{
		clone = clone_map(map->map);
		if (flood_fill_element(clone, px, py, fill_chars[i]) != 0)
		{
			free_map(clone);
			printf("map is invalid : player can fall in void\n");
			clean_exit_mand(data);
			exit(1);
		}
		free_map(clone);
	}
}

void	check_map_ff(t_data *data, t_map *map)
{
	int	px;
	int	py;

	get_player_pos(map->map, &px, &py);
	check_map_floods(data, map, px, py);
	if (check_player(map))
	{
		clean_exit_mand(data);
		exit(1);
	}
	if (check_invalid(map->map) < 0)
	{
		printf("map is invalid : wrong type of tile\n");
		clean_exit_mand(data);
		exit(1);
	}
}
