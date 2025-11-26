/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:48:01 by hugz              #+#    #+#             */
/*   Updated: 2025/11/26 13:48:52 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

int	is_wall_hit(t_data *data, int mx, int my)
{
	if (!is_valid_map(data))
		return (0);
	if (my < 0 || my >= data->map->height)
		return (0);
	if (mx < 0 || mx >= (int)ft_strlen(data->map->map[my]))
		return (0);
	return (data->map->map[my][mx] == '1' || data->map->map[my][mx] == '2'
		|| data->map->map[my][mx] == '3');
}

int	is_door_hit(t_data *data, int mx, int my)
{
	if (!is_valid_map(data))
		return (0);
	if (my < 0 || my >= data->map->height)
		return (0);
	if (mx < 0 || mx >= (int)ft_strlen(data->map->map[my]))
		return (0);
	return (data->map->map[my][mx] == 'L' || data->map->map[my][mx] == 'D');
}

int	is_mob(t_data *data, int mx, int my)
{
	if (!is_valid_map(data))
		return (0);
	if (my < 0 || my >= data->map->height)
		return (0);
	if (mx < 0 || mx >= (int)ft_strlen(data->map->map[my]))
		return (0);
	return (data->map->map[my][mx] == 'M');
}

#endif