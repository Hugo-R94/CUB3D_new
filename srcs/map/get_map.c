/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:57:27 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/15 15:53:18 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../includes/cub3d.h"
#include <stdlib.h>
#include <time.h>

void	free_tab(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
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

int name_checker(char *str)
{
    int len;

    if (!str)
        return (0);
    len = ft_strlen(str);
    if (len < 4)
        return (0);
    while (len > 0 && (str[len-1] == '\n' || str[len-1] == ' '))
        len--;
    if (len < 4)
        return (0);
    if (ft_strcmp(str + len - 4, ".cub") == 0)
        return (1);
    return (0);
}


char	**add_line_to_map(char **map, char *line, int size)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (size + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < size - 1 && map && map[i])
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = ft_strdup(line);
	new_map[i + 1] = (NULL);
	free(map);
	return (new_map);
}

int	parse_color(char *line)
{
	int	r;
	int	g;
	int	b;

	if (sscanf(line, "%d,%d,%d", &r, &g, &b) != 3)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

int	parse_line(t_map *data, char *line, int start_map)
{
	if (!line[0])
		return (start_map);
	if (!start_map)
	{
		if (!ft_strncmp(line, "NO ", 3))
			data->textures[0].path = ft_strdup(line + 3);
		else if (!ft_strncmp(line, "SO ", 3))
			data->textures[1].path = ft_strdup(line + 3);
		else if (!ft_strncmp(line, "WE ", 3))
			data->textures[2].path = ft_strdup(line + 3);
		else if (!ft_strncmp(line, "EA ", 3))
			data->textures[3].path = ft_strdup(line + 3);
		else if (line[0] == 'F')
			data->f_color = parse_color(line + 2);
		else if (line[0] == 'C')
			data->c_color = parse_color(line + 2);
		else
			return (1);
	}
	return (start_map);
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

t_map	*parse_file(int fd)
{
	t_map	*data;
	char	*line;
	int		map_index;
	int		start_map;

	map_index = 0;
	start_map = 0;
	data = calloc(1, sizeof(t_map));
	line = get_next_line(fd, 0);
	while (line )
	{
		if (!start_map)
		{
			if (!ft_strncmp(line, "NO ", 3))
				data->textures[0].path = ft_strdup(line + 3);
			else if (!ft_strncmp(line, "SO ", 3))
				data->textures[1].path = ft_strdup(line + 3);
			else if (!ft_strncmp(line, "WE ", 3))
				data->textures[2].path = ft_strdup(line + 3);
			else if (!ft_strncmp(line, "EA ", 3))
				data->textures[3].path = ft_strdup(line + 3);
			else if (line[0] == 'F')
				data->f_color = parse_color(line + 2);
			else if (line[0] == 'C')
				data->c_color = parse_color(line + 2);
			else if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
				start_map = 1;
		}	
		if (start_map && !is_line_empty(line))
		{
			data->map = add_line_to_map(data->map, line, map_index + 1);
			map_index++;
		}
		free(line);
		line = get_next_line(fd, 0);
	}
	return (data);
}
