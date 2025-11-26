/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:46:21 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 18:54:26 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

void	fill_room_borders(char **map, t_room *room, int params[4])
{
	int	i;
	int	j;
	int	nx;
	int	ny;

	j = -1;
	while (++j < room->h)
	{
		i = -1;
		while (++i < room->w)
		{
			nx = room->x + i;
			ny = room->y + j;
			if (nx <= 0 || nx >= params[0] - 1
				|| ny <= 0 || ny >= params[1] - 1)
				continue ;
			if (i == 0 || i == room->w - 1 || j == 0 || j == room->h - 1)
				map[ny][nx] = '1';
			else
				map[ny][nx] = '0';
		}
	}
}

void	place_enemies(char **map, t_room *room)
{
	int	enemies;
	int	placed;
	int	ex;
	int	ey;

	enemies = 2 + rand() % 2;
	placed = 0;
	while (placed < enemies)
	{
		ex = room->x + 1 + rand() % (room->w - 2);
		ey = room->y + 1 + rand() % (room->h - 2);
		if (map[ey][ex] == '0')
		{
			if (placed % 2 == 0)
				map[ey][ex] = 'M';
			else
				map[ey][ex] = 'B';
			placed++;
		}
	}
}

t_room	create_room(char **map, int pos[2], int wh[2], int params[2])
{
	t_room	room;

	room.x = pos[0];
	room.y = pos[1];
	room.w = wh[0];
	room.h = wh[1];
	room.cx = pos[0] + wh[0] / 2;
	room.cy = pos[1] + wh[1] / 2;
	fill_room_borders(map, &room, (int [4]){params[0], params[1], 0, 0});
	place_enemies(map, &room);
	return (room);
}

#endif