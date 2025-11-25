/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:47:25 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/24 16:32:28 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

void	new_map_random(t_data *data)
{
	int	len;

	if (data->map)
		free_map(data->map->map);
	data->map->map = make_map(data);
	printf("debut\n");
	data->map->height = 0;
	data->map->width = 0;
	while (data->map->map[data->map->height])
	{
		len = ft_strlen(data->map->map[data->map->height]);
		if (len > data->map->width)
			data->map->width = len;
		data->map->height++;
	}
	get_player_original_pos(data);
	get_exit_pos(data);
	print_map(data->map->map);
	init_mob(data);
}

int	main(void)
{
	t_data	*data;

	data = init_data();
	mlx_game_loop(data);
	return (0);
}

#endif