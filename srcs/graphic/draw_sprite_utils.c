/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:40:31 by hugz              #+#    #+#             */
/*   Updated: 2025/11/26 11:44:39 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

float	calc_distance(t_data *data, float x, float y)
{
	float	dx;
	float	dy;

	dx = x - data->player.px;
	dy = y - data->player.py;
	return (sqrt(dx * dx + dy * dy));
}

float	get_angle_to_sprite(t_data *data, float x, float y)
{
	float	dx;
	float	dy;
	float	angle_to_sprite;
	float	relative_angle;

	dx = x - data->player.px;
	dy = y - data->player.py;
	angle_to_sprite = atan2(dy, dx);
	relative_angle = angle_to_sprite - data->player.pa;
	while (relative_angle > M_PI)
		relative_angle -= 2 * M_PI;
	while (relative_angle < -M_PI)
		relative_angle += 2 * M_PI;
	return (relative_angle);
}

int	get_screen_x(float relative_angle, float fov)
{
	return ((int)((relative_angle / fov + 0.5) * 640));
}

int	get_tex_coord(int screen, int start, float ratio, int max)
{
	int	coord;

	coord = (int)((screen - start) * ratio);
	if (coord < 0)
		coord = 0;
	if (coord >= max)
		coord = max - 1;
	return (coord);
}

void	compute_ratios(float ratios[2], t_txt *tex, int bounds[7])
{
	ratios[0] = (float)tex->img.width / (float)bounds[1];
	ratios[1] = (float)tex->img.height / (float)bounds[0];
}

#endif