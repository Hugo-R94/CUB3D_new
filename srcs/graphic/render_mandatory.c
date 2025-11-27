/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mandatory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:01:42 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/27 12:03:22 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifndef BONUS

void	draw_wall_column_txt(t_data *data, int x, float ra)
{
	t_txt	*txt;
	int		full_line_h;
	float	wall_x;
	int		tex_x;
	float	dist[4];

	get_distances(data, ra, &dist[0], &dist[1]);
	txt = find_wall_txt(data, dist[0], dist[1], ra);
	dist[2] = fmin(dist[0], dist[1]);
	dist[3] = get_corrected_distance(data, ra, dist[2]);
	calculate_line_height(data, dist[3], &full_line_h);
	wall_x = get_wall_x(data, (float []){dist[0], dist[1], dist[2]}, ra);
	tex_x = get_texture_x(&txt->img, wall_x);
	render_column(data, &txt->img, (int []){x, tex_x}, full_line_h);
}

void	process_single_ray(t_data *data, int i, float ra)
{
	ra = normalize_angle(ra);
	draw_wall_column_txt(data, i, ra);
}

void	draw_walls_3d(t_data *data)
{
	float	ra;
	int		i;

	if (!data || !data->map || !data->map->map)
		return ;
	i = 0;
	while (i < data->res_x)
	{
		ra = data->player.pa - (data->fov / 2) + (data->fov * i) / data->res_x;
		process_single_ray(data, i, ra);
		i++;
	}
}

#endif