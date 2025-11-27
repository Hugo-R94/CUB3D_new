/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mob_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:46:14 by hugz              #+#    #+#             */
/*   Updated: 2025/11/27 13:47:09 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

float	calculate_mob_distance(t_data *data, int i)
{
	float	dx;
	float	dy;

	dx = data->mob[i].mx - data->player.px;
	dy = data->mob[i].my - data->player.py;
	return (sqrt(dx * dx + dy * dy));
}

float	get_relative_angle(t_data *data, int i)
{
	float	dx;
	float	dy;
	float	angle_to_mob;
	float	relative_angle;

	dx = data->mob[i].mx - data->player.px;
	dy = data->mob[i].my - data->player.py;
	angle_to_mob = atan2(dy, dx);
	relative_angle = angle_to_mob - data->player.pa;
	while (relative_angle > M_PI)
		relative_angle -= 2 * M_PI;
	while (relative_angle < -M_PI)
		relative_angle += 2 * M_PI;
	return (relative_angle);
}

void	get_mob_ratios(t_txt *tex, int *bounds, float *ratios, int x)
{
	ratios[0] = (float)tex->img.width / (float)bounds[1];
	ratios[1] = (float)tex->img.height / (float)bounds[0];
	ratios[2] = get_tex_coord(x, bounds[2], ratios[0], tex->img.width);
}

void	draw_px_info(t_data *data, int index, int color, float *ratios)
{
	data->render_gmp->pixels[index].color = color;
	data->render_gmp->pixels[index].depth = ratios[4];
	data->render_gmp->pixels[index].type = PX_MOB;
	data->render_gmp->pixels[index].id = (int)ratios[5];
}

#endif