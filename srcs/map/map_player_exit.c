/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:45:33 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 18:58:17 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

void	setup_player_exit(char **map, int map_w, int map_h)
{
	int		pos[2];
	int		**dist;
	t_point	*queue;
	int		params[4];
	int		exit[2];

	if (!find_player_pos(map, map_w, map_h, pos))
		return ;
	dist = init_distance_grid(map_w, map_h);
	queue = malloc(sizeof(t_point) * map_w * map_h);
	queue[0] = (t_point){pos[0], pos[1]};
	dist[pos[1]][pos[0]] = 0;
	params[0] = map_w;
	params[1] = map_h;
	params[2] = 0;
	params[3] = 1;
	flood_fill(map, dist, queue, params);
	exit[0] = pos[0];
	exit[1] = pos[1];
	find_farthest_point(dist, map_w, map_h, exit);
	map[exit[1]][exit[0]] = 'X';
	free(queue);
	while (--map_h >= 0)
		free(dist[map_h]);
	free(dist);
}

#endif