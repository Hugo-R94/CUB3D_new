/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:47:25 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/30 15:28:41 by hrouchy          ###   ########.fr       */
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
	print_map(data->map->map);
	printf("fin\n");
}

int	main(void)
{
	t_data	*data;

	data = init_data();
	printf("px = %f | py = %f\n", data->player.px, data->player.py);
	mlx_game_loop(data);
	return (0);
}

#endif