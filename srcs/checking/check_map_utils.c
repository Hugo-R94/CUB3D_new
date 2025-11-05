/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:13:57 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/28 14:20:33 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**allocate_clone(char **map)
{
	char	**new_map;
	int		i;
	int		j;

	i = 0;
	while (map[i])
		i++;
	new_map = malloc(sizeof(char *) * (i + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		new_map[i] = malloc(sizeof(char) * (j + 1));
		if (!new_map[i])
			return (NULL);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

char	**clone_map(char **map)
{
	char	**new_map;
	int		i;
	int		j;

	new_map = allocate_clone(map);
	if (!new_map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			new_map[i][j] = map[i][j];
			j++;
		}
		new_map[i][j] = '\0';
		i++;
	}
	return (new_map);
}

int	flood_fill_element(char **map, int x, int y, char element)
{
	int	count;

	count = 0;
	if (y < 0 || x < 0 || !map[y] || x >= ft_strlen(map[y]))
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	if (map[y][x] == element)
		count = 1;
	map[y][x] = 'V';
	count += flood_fill_element(map, x + 1, y, element);
	count += flood_fill_element(map, x - 1, y, element);
	count += flood_fill_element(map, x, y + 1, element);
	count += flood_fill_element(map, x, y - 1, element);
	return (count);
}
