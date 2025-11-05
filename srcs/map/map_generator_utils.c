/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:22:15 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/17 12:25:11 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#ifdef BONUS
int	has_door_in_line_or_column(char **map, int x, int y)
{
	int	j;
	int	i;

	i = -1;
	j = -1;
	while (map[++j])
		if (map[j][x] == 'D')
			return (1);
	while (map[y][++i])
		if (map[y][i] == 'D')
			return (1);
	return (0);
}

static int should_keep_wall(char **map, int y, int x, int map_w, int map_h)
{
    int dy, dx, ny, nx;

    for (dy = -1; dy <= 1; dy++)
    {
        for (dx = -1; dx <= 1; dx++)
        {
            if (dx == 0 && dy == 0)
                continue;
            ny = y + dy;
            nx = x + dx;
            if (ny < 0 || ny >= map_h || nx < 0 || nx >= map_w)
                continue;
            if (map[ny][nx] == '0' || map[ny][nx] == 'D')
                return 1;
        }
    }
    return 0;
}


void clean_map(char **map, int map_w, int map_h)
{
    int y, x;

    for (y = 0; y < map_h; y++)
    {
        for (x = 0; x < map_w; x++)
        {
            if (map[y][x] == '1' && !should_keep_wall(map, y, x, map_w, map_h))
                map[y][x] = ' ';
        }
    }
}


int	is_too_close_x(t_room *rooms, int room_count, int x, int w)
{
	int	i;
	int	nx1;
	int	nx2;
	int	rx1;
	int	rx2;

	nx1 = x;
	nx2 = x + w;
	i = -1;
	while (++i < room_count)
	{
		rx1 = rooms[i].x - 2;
		rx2 = rooms[i].x + rooms[i].w + 2;
		if (!(nx2 < rx1 || nx1 > rx2))
			return (1);
	}
	return (0);
}

int	is_too_close_y(t_room *rooms, int room_count, int y, int h)
{
	int	i;
	int	ny1;
	int	ny2;
	int	ry1;
	int	ry2;

	ny1 = y;
	ny2 = y + h;
	i = -1;
	while (++i < room_count)
	{
		ry1 = rooms[i].y - 2;
		ry2 = rooms[i].y + rooms[i].h + 2;
		if (!(ny2 < ry1 || ny1 > ry2))
			return (1);
	}
	return (0);
}

// int	is_too_close(t_room *rooms, int room_count, int x, int y, int w, int h)
// {
// 	int i;
// 	int rx1;
// 	int rx2;
// 	int ry1;
// 	int ry2;
// 	int	nx1;	
// 	int	nx2;	
// 	int	ny1;	
// 	int	ny2;

// 	i = -1;
// 	while ( ++i < room_count)
// 	{
// 		rx1 = rooms[i].x - 2;
// 		ry1 = rooms[i].y - 2;
// 		rx2 = rooms[i].x + rooms[i].w + 2;
// 		ry2 = rooms[i].y + rooms[i].h + 2;
// 		nx1 = x;
// 		ny1 = y;
// 		nx2 = x + w;
// 		ny2 = y + h;
// 		if (!(nx2 < rx1 || nx1 > rx2 || ny2 < ry1 || ny1 > ry2))
// 			return 1;
// 	}
// 	return 0;
// }

int	is_potential_door(char **m, int x, int y)
{
	int	cond1;
	int	cond2;

	if (x <= 0 || y <= 0 || !m[y + 1] || !m[y][x + 1])
		return (0);
	cond1 = (m[y + 1][x] == '1'
			&& m[y - 1][x] == '1'
			&& m[y][x + 1] == '0'
			&& m[y][x - 1] == '0');
	cond2 = (m[y + 1][x] == '0'
			&& m[y - 1][x] == '0'
			&& m[y][x + 1] == '1'
			&& m[y][x - 1] == '1');
	return (cond1 || cond2);
}

void	setup_doors(char **m)
{
	int	x;
	int	y;

	y = 0;
	while (m[y])
	{
		x = 0;
		while (m[y][x])
		{
			if (m[y][x] == '0'
				&& is_potential_door(m, x, y)
				&& !has_door_in_line_or_column(m, x, y))
				m[y][x] = 'D';
			x++;
		}
		y++;
	}
}
#endif