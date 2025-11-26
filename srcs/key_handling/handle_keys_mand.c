/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_mand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:14:29 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/25 14:24:01 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifndef BONUS

# define MOVE_SPEED 0.02
# define ROT_SPEED 0.006	

static void	update_direction_vector(t_data *data)
{
	data->player.pdx = cos(data->player.pa) * 3;
	data->player.pdy = sin(data->player.pa) * 3;
}

void	handle_rotation(t_data *data)
{
	if (data->a_is_press)
	{
		data->player.pa -= data->player.rot_speed;
		if (data->player.pa < 0)
			data->player.pa += 2 * M_PI;
		update_direction_vector(data);
	}
	if (data->d_is_press)
	{
		data->player.pa += data->player.rot_speed;
		if (data->player.pa > 2 * M_PI)
			data->player.pa -= 2 * M_PI;
		update_direction_vector(data);
	}
}

void	handle_movement(t_data *data)
{
	double	next_px;
	double	next_py;

	if (data->w_is_press)
	{
		next_px = data->player.px + cos(data->player.pa)
			* data->player.mouv_speed;
		next_py = data->player.py + sin(data->player.pa)
			* data->player.mouv_speed;
		if (data->map->map[(int)next_py][(int)data->player.px] != '1')
			data->player.py = next_py;
		if (data->map->map[(int)data->player.py][(int)next_px] != '1')
			data->player.px = next_px;
	}
	if (data->s_is_press)
	{
		next_px = data->player.px - cos(data->player.pa)
			* data->player.mouv_speed;
		next_py = data->player.py - sin(data->player.pa)
			* data->player.mouv_speed;
		if (data->map->map[(int)(next_py)][(int)(data->player.px)] != '1')
			data->player.py = next_py;
		if (data->map->map[(int)(data->player.py)][(int)(next_px)] != '1')
			data->player.px = next_px;
	}
}

int	handle_key_press(int keycode, t_data *data)
{
	(void)data;
	if (keycode == 97)
		data->a_is_press = 1;
	if (keycode == 100)
		data->d_is_press = 1;
	if (keycode == 115)
		data->s_is_press = 1;
	if (keycode == 119)
		data->w_is_press = 1;
	return (0);
}

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == 65307)
		clean_exit_mand(data);
	if (keycode == 97)
		data->a_is_press = 0;
	if (keycode == 100)
		data->d_is_press = 0;
	if (keycode == 115)
		data->s_is_press = 0;
	if (keycode == 119)
		data->w_is_press = 0;
	return (0);
}
#endif	