/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:57:27 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/25 15:14:01 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../includes/cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	check_invalid(char **map)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (map[i])
	{
		y = 0;
		while (map[i][y])
		{
			if (map[i][y] != '1' && map[i][y] != 'S' && map[i][y] != '0'
				&& map[i][y] != 'N' && map[i][y] != 'W' && map[i][y] != 'E'
				&& map[i][y] != '\n' && map[i][y] != ' ')
				return (-1);
			y++;
		}
		i++;
	}
	return (1);
}

void	print_map(char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '0')
				printf("%s%c%s", GRN, map[y][x], RESET);
			else if (map[y][x] == '1' || map[y][x] == '2' || map[y][x] == '3')
				printf("%s%c%s", BLU, map[y][x], RESET);
			else if (map[y][x] == 'D')
				printf("%s%c%s", CYN, map[y][x], RESET);
			else if (map[y][x] == 'X' || map[y][x] == 'N')
				printf("%s%c%s", YEL, map[y][x], RESET);
			else if (map[y][x] == 'M')
				printf("%s%c%s", RED, map[y][x], RESET);
			else
				printf("%c", map[y][x]);
		}
		printf("\n");
	}
}
