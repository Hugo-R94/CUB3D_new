/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:39:25 by hugz              #+#    #+#             */
/*   Updated: 2025/11/27 13:40:44 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

void	cast_rays(t_data *data, t_raycast *raycast)
{
	cast_horizontal_ray(data, &raycast->rx_h, &raycast->ry_h, raycast->ra);
	cast_vertical_ray(data, &raycast->rx_v, &raycast->ry_v, raycast->ra);
}

void	cast_doors_rays(t_data *data, t_raycast *raycast)
{
	cast_horizontal_door_ray(data, &raycast->rx_h, &raycast->ry_h, raycast->ra);
	cast_vertical_door_ray(data, &raycast->rx_v, &raycast->ry_v, raycast->ra);
}

void	calculate_distances(t_data *data, t_raycast *raycast,
	float *dist_h, float *dist_v)
{
	*dist_h = sqrtf(powf(raycast->rx_h - data->player.px, 2)
			+ powf(raycast->ry_h - data->player.py, 2));
	*dist_v = sqrtf(powf(raycast->rx_v - data->player.px, 2)
			+ powf(raycast->ry_v - data->player.py, 2));
}

//dist[0] = dist_h | dist[1] = dist_v

void	get_final_distance(t_data *data, float dist[2],
	float ra, float *dist_final)
{
	float	dist_raw;

	if (dist[1] < dist[0])
	{
		dist_raw = dist[1];
	}
	else
	{
		dist_raw = dist[0];
	}
	if (data->shift_is_press == 1)
		*dist_final = dist_raw;
	else
		*dist_final = dist_raw * cos(data->player.pa - ra);
	if (*dist_final < 0.1f)
		*dist_final = 0.1f;
}

//line[0] = line_h | line[1] = line_off
void	calculate_wall_dimensions(t_data *data, float dist_final,
				int *line[2], int factor)
{
	float	plane_dist;
	int		screen_h;
	int		screen_w;

	screen_h = 480;
	screen_w = 640;
	plane_dist = (screen_w / 2.0f) / tan(data->fov / 2.0f);
	*line[0] = (int)(plane_dist / dist_final * factor);
	*line[1] = (screen_h - *line[0]) / 2
		+ data->tilt + data->player.pl_height;
}

#endif
