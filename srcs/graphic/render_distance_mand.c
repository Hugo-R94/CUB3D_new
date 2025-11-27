/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_distance_mand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:52:10 by hugz              #+#    #+#             */
/*   Updated: 2025/11/27 11:58:24 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifndef BONUS

float	calculate_distance(float x1, float y1, float x2, float y2)
{
	float	dx;
	float	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrtf(dx * dx + dy * dy));
}

void	get_distances(t_data *data, float ra, float *dist_h, float *dist_v)
{
	float	rx_h;
	float	ry_h;
	float	rx_v;
	float	ry_v;

	cast_horizontal_ray(data, &rx_h, &ry_h, ra);
	cast_vertical_ray(data, &rx_v, &ry_v, ra);
	*dist_h = calculate_distance(data->player.px, data->player.py, rx_h, ry_h);
	*dist_v = calculate_distance(data->player.px, data->player.py, rx_v, ry_v);
}

float	get_corrected_distance(t_data *data, float ra, float dist)
{
	float	dist_final;

	dist_final = dist;
	dist_final *= cos(data->player.pa - ra);
	if (dist_final < 0.1f)
		dist_final = 0.1f;
	return (dist_final);
}

int	calculate_line_height(t_data *data, float dist_final, int *full_h)
{
	float	plane_dist;
	int		line_h;

	plane_dist = (data->res_x / 2.0f) / tan(data->fov / 2.0f);
	line_h = (int)(plane_dist / dist_final);
	*full_h = line_h;
	if (line_h > data->res_y)
		line_h = data->res_y;
	return (line_h);
}

#endif