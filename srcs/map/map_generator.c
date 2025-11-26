/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:47:20 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 18:52:32 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

int	try_place_room(char **map, t_room *rooms, int params[4])
{
	int	wh[2];
	int	max[2];
	int	xy[2];

	wh[0] = 7 + rand() % 4;
	wh[1] = 7 + rand() % 4;
	max[0] = params[0] - wh[0] - 2;
	max[1] = params[1] - wh[1] - 2;
	if (max[0] <= 0 || max[1] <= 0)
		return (0);
	xy[0] = 1 + rand() % max[0];
	xy[1] = 1 + rand() % max[1];
	if (is_too_close_x(rooms, params[2], xy[0], wh[0])
		&& is_too_close_y(rooms, params[2], xy[1], wh[1]))
		return (0);
	rooms[params[2]] = create_room(map, xy, wh,
			(int [2]){params[0], params[1]});
	if (params[2] > 0)
		create_corridor(map, rooms[params[2] - 1], rooms[params[2]],
			(int [2]){params[0], params[1]});
	return (1);
}

char	**generate_map(int map_w, int map_h)
{
	char	**map;
	int		params[4];
	t_room	rooms[10];

	map = alloc_map(map_w, map_h);
	params[0] = map_w;
	params[1] = map_h;
	params[2] = 0;
	params[3] = 0;
	while (params[2] < 3 + rand() % 4 && params[3] < 200)
	{
		params[3]++;
		if (try_place_room(map, rooms, params))
			params[2]++;
	}
	return (map);
}

char	**make_map(t_data *data)
{
	char	**map;

	srand(time(NULL));
	map = generate_map(data->map_w, data->map_h);
	clean_map(map, data->map_w, data->map_h);
	setup_player_exit(map, data->map_w, data->map_h);
	reparse(map);
	return (map);
}

#endif