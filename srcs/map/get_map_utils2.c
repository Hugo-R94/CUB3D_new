/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:24:59 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 15:29:40 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	name_checker(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 4)
		return (0);
	while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == ' '))
		len--;
	if (len < 4)
		return (0);
	if (ft_strcmp(str + len - 4, ".cub") == 0)
		return (1);
	return (0);
}

char	**ft_realloc(char **map, int size)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (size + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < size && map && map[i])
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = NULL;
	free(map);
	return (new_map);
}

int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
