/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_coord_mand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:53:04 by hugz              #+#    #+#             */
/*   Updated: 2025/11/27 11:59:05 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifndef BONUS

float	get_horizontal_wall_x(float hit_x, float ra)
{
	float	wall_x;

	wall_x = hit_x - floor(hit_x);
	if (sin(ra) > 0)
		wall_x = 1.0f - wall_x;
	return (wall_x);
}

float	get_vertical_wall_x(float hit_y, float ra)
{
	float	wall_x;

	wall_x = hit_y - floor(hit_y);
	if (cos(ra) < 0)
		wall_x = 1.0f - wall_x;
	return (wall_x);
}

float	get_wall_x(t_data *data, float dist[3], float ra)
{
	float	hit[2];
	float	wall_x;

	hit[0] = data->player.px + dist[2] * cos(ra);
	hit[1] = data->player.py + dist[2] * sin(ra);
	if (dist[0] < dist[1])
		wall_x = get_horizontal_wall_x(hit[0], ra);
	else
		wall_x = get_vertical_wall_x(hit[1], ra);
	return (wall_x);
}

#endif