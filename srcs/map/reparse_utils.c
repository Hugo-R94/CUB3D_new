/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reparse_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:47:15 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/17 12:25:45 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#ifdef BONUS
// ---- Nord ----
void	reparse_north(char **map, int py)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				if (y < py)
					map[y][x] = '1';
				else if (y == py)
					map[y][x] = '2';
				else
					map[y][x] = '3';
			}
			x++;
		}
		y++;
	}
}

// ---- Sud ----
void	reparse_south(char **map, int py)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				if (y > py)
					map[y][x] = '1';
				else if (y == py)
					map[y][x] = '2';
				else
					map[y][x] = '3';
			}
			x++;
		}
		y++;
	}
}

// ---- Est ----
void	reparse_east(char **map, int px)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				if (x > px)
					map[y][x] = '1';
				else if (x == px)
					map[y][x] = '2';
				else
					map[y][x] = '3';
			}
			x++;
		}
		y++;
	}
}

// ---- Ouest ----
void	reparse_west(char **map, int px)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				if (x < px)
					map[y][x] = '1';
				else if (x == px)
					map[y][x] = '2';
				else
					map[y][x] = '3';
			}
			x++;
		}
		y++;
	}
}
#endif