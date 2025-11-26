/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:57:00 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 15:57:19 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
