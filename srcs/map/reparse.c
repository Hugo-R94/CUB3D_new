/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reparse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:03:40 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/17 12:25:58 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdlib.h>
#include <time.h>
#ifdef BONUS
// ---- Router ----
void	base_reparse(char **map, char p_dir, int px, int py)
{
	if (p_dir == 'N')
		reparse_north(map, py);
	else if (p_dir == 'S')
		reparse_south(map, py);
	else if (p_dir == 'E')
		reparse_east(map, px);
	else if (p_dir == 'O')
		reparse_west(map, px);
}

int	is_tree(char c)
{
	return (c == 'T' || c == '2' || c == '3');
}

int	count_tree(char **map, int x, int y)
{
	int	count;

	count = 0;
	if (!map[x + 1] || !map[x][y + 1] || x == 0 || y == 0)
	{
		if (rand() % 3 == 0)
			return (3);
		return (4);
	}
	if (map[x + 1] && map[x + 1][y] && is_tree(map[x + 1][y]))
		count++;
	if (x > 0 && map[x - 1][y] && is_tree(map[x - 1][y]))
		count++;
	if (map[x][y + 1] && is_tree(map[x][y + 1]))
		count++;
	if (y > 0 && map[x][y - 1] && is_tree(map[x][y - 1]))
		count++;
	if (rand() % 5 == 0)
		count++;
	return (count);
}

void	reparse_forest(char **map)
{
	int	x;
	int	y;
	int	tree_counter;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'T')
			{
				tree_counter = count_tree(map, x, y);
				if (tree_counter < 3)
					map[x][y] = 'B';
				else if (tree_counter < 4)
					map[x][y] = '2';
				else
					map[x][y] = '3';
			}
			y++;
		}
		x++;
	}
}

void	reparse(char **map)
{
	int		px;
	int		py;
	char	p_dir;

	p_dir = get_player_pos(map, &px, &py);
	printf("player dir = %c, px = %d | py = %d\n", p_dir, px, py);
	base_reparse(map, p_dir, px, py);
}
#endif