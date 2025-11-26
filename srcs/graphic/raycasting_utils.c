/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:12:32 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/26 13:48:23 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_map(t_data *data)
{
	if (!data || !data->map || !data->map->map)
	{
		printf("y a pas la map lol\n");
		return (0);
	}
	return (1);
}

#ifndef BONUS

int	is_wall_hit(t_data *data, int mx, int my)
{
	if (!is_valid_map(data))
		return (0);
	if (my < 0 || my >= data->map->height)
		return (0);
	if (mx < 0 || mx >= (int)ft_strlen(data->map->map[my]))
		return (0);
	return (data->map->map[my][mx] == '1');
}
#endif

float	normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void	init_line_params(t_line *line, float x1, float y1)
{
	if (fabs(line->dx) > fabs(line->dy))
		line->steps = fabs(line->dx);
	else
		line->steps = fabs(line->dy);
	if (line->steps == 0)
		line->steps = 1;
	line->x_inc = line->dx / line->steps;
	line->y_inc = line->dy / line->steps;
	line->x = x1;
	line->y = y1;
}
