/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:06:43 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 14:10:44 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

static void	move_forward(t_data *data)
{
	double	next_px;
	double	next_py;
	double	move_speed;

	move_speed = data->player.mouv_speed;
	next_px = data->player.px + cos(data->player.pa) * move_speed;
	next_py = data->player.py + sin(data->player.pa) * move_speed;
	if (!check_wall_collision(data, data->player.px, next_py, 0.1))
		data->player.py = next_py;
	if (!check_wall_collision(data, next_px, data->player.py, 0.1))
		data->player.px = next_px;
}

static void	move_backward(t_data *data)
{
	double	next_px;
	double	next_py;
	double	move_speed;

	move_speed = data->player.mouv_speed;
	next_px = data->player.px - cos(data->player.pa) * move_speed;
	next_py = data->player.py - sin(data->player.pa) * move_speed;
	if (!check_wall_collision(data, data->player.px, next_py, 0.1))
		data->player.py = next_py;
	if (!check_wall_collision(data, next_px, data->player.py, 0.1))
		data->player.px = next_px;
}

static void	strafe_right(t_data *data)
{
	double	next_px;
	double	next_py;
	double	move_speed;

	move_speed = data->player.mouv_speed;
	next_px = data->player.px - sin(data->player.pa) * move_speed;
	next_py = data->player.py + cos(data->player.pa) * move_speed;
	if (!check_wall_collision(data, data->player.px, next_py, 0.1))
		data->player.py = next_py;
	if (!check_wall_collision(data, next_px, data->player.py, 0.1))
		data->player.px = next_px;
}

static void	strafe_left(t_data *data)
{
	double	next_px;
	double	next_py;
	double	move_speed;

	move_speed = data->player.mouv_speed;
	next_px = data->player.px + sin(data->player.pa) * move_speed;
	next_py = data->player.py - cos(data->player.pa) * move_speed;
	if (!check_wall_collision(data, data->player.px, next_py, 0.1))
		data->player.py = next_py;
	if (!check_wall_collision(data, next_px, data->player.py, 0.1))
		data->player.px = next_px;
}

void	handle_movement(t_data *data)
{
	static int	up = 1;

	if (data->w_is_press || data->d_is_press
		|| data->s_is_press || data->a_is_press)
		update_head_bob(data, &up);
	if (data->w_is_press)
		move_forward(data);
	if (data->s_is_press)
		move_backward(data);
	if (data->d_is_press)
		strafe_right(data);
	if (data->a_is_press)
		strafe_left(data);
}

#endif