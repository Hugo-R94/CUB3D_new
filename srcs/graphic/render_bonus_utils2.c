/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:43:19 by hugz              #+#    #+#             */
/*   Updated: 2025/11/27 13:54:53 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

void	get_texture_info(t_data *data, float dist[2],
	t_raycast *raycast, t_txt **txt)
{
	float	hit_x;
	float	hit_y;
	float	wall_x;
	float	dist_raw;

	if (dist[1] < dist[0])
		dist_raw = dist[1];
	else
		dist_raw = dist[0];
	*txt = find_wall_txt(data, dist[0], dist[1], raycast);
	hit_x = data->player.px + dist_raw * cos(raycast->ra);
	hit_y = data->player.py + dist_raw * sin(raycast->ra);
	wall_x = get_wall_x_coord(dist[0], dist[1],
			(float [2]){hit_x, hit_y}, raycast->ra);
	raycast->tex_x = get_texture_x(&(*txt)->img, wall_x);
}

void	render_column(t_data *data, int value[5],
	t_txt *txt, float dist_final)
{
	draw_ceiling(data, value[0], value[1], data->ceiling);
	draw_wall_column(data, value, &txt->img, dist_final);
	draw_floor(data, value[0], value[3] + value[2]);
}

/* Fonction helper pour stocker les coordonnées du rayon */
void	store_ray_coords(t_data *data, int i,
	t_raycast *ray, float dists[2])
{
	if (dists[0] < dists[1])
	{
		data->raycast_f[i].rx = ray->rx_h;
		data->raycast_f[i].ry = ray->ry_h;
		data->raycast_f[i].rx_final = ray->rx_h;
		data->raycast_f[i].ry_final = ray->ry_h;
	}
	else
	{
		data->raycast_f[i].rx = ray->rx_v;
		data->raycast_f[i].ry = ray->ry_v;
		data->raycast_f[i].rx_final = ray->rx_v;
		data->raycast_f[i].ry_final = ray->ry_v;
	}
	data->raycast_f[i].ra = ray->ra;
}

void	get_floor_pos(double *fx, double *fy, t_data *data, double *ray)
{
	double	row_dist;

	row_dist = ray[2];
	*fx = data->player.px + row_dist * ray[0];
	*fy = data->player.py + row_dist * ray[1];
}

#endif