/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:40:44 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 14:41:05 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

void	update_mouse_pos_menu(t_data *data, int x, int y)
{
	float	scale[2];
	int		mouse_scaled_x;
	int		mouse_scaled_y;

	scale[0] = 640.0f / (float)data->res_x;
	scale[1] = 480.0f / (float)data->res_y;
	mouse_scaled_x = (int)(x * scale[0]);
	mouse_scaled_y = (int)(y * scale[1]);
	data->mouse.x_accel = mouse_scaled_x - data->mouse.old_mouse_x;
	data->mouse.y_accel = mouse_scaled_y - data->mouse.old_mouse_y;
	data->mouse.mouse_x = mouse_scaled_x;
	data->mouse.mouse_y = mouse_scaled_y;
	data->mouse.old_mouse_x = mouse_scaled_x;
	data->mouse.old_mouse_y = mouse_scaled_y;
}

static void	apply_rotation(t_data *data, int delta_x, int delta_y)
{
	data->player.pa += delta_x * data->mouse.sensitivity / 1.5;
	data->player.parralax_x += (delta_x * data->mouse.sensitivity)
		* (18.0f * M_PI);
	if (data->player.pa < 0)
		data->player.pa += 2.0f * M_PI;
	else if (data->player.pa >= 2.0f * M_PI)
		data->player.pa -= 2.0f * M_PI;
	data->tilt -= (delta_y * (data->mouse.sensitivity * 350));
	if (data->tilt > 200)
		data->tilt = 200;
	if (data->tilt < -200)
		data->tilt = -200;
}

void	update_mouse_pos_game(t_data *data, int x, int y)
{
	int	center_x;
	int	center_y;
	int	delta_x;
	int	delta_y;

	if (!data || !data->win)
		return ;
	center_x = data->res_x / 2;
	center_y = data->res_y / 2;
	delta_x = x - center_x;
	delta_y = y - center_y;
	apply_rotation(data, delta_x, delta_y);
	data->mouse.x_accel = delta_x;
	data->mouse.y_accel = delta_y;
	data->mouse.mouse_x = center_x;
	data->mouse.mouse_y = center_y;
	data->mouse.old_mouse_x = center_x;
	data->mouse.old_mouse_y = center_y;
	if (data->win->win && data->win->mlx)
		mlx_mouse_move(data->win->mlx, data->win->win, center_x, center_y);
}

static void	check_button_hover(t_data *data)
{
	int			i;
	t_button	*b;

	data->mouse.button_hovered = -1;
	i = -1;
	while (data->current_buttons[++i].on_click)
	{
		b = &data->current_buttons[i];
		if (data->mouse.mouse_x >= b->x
			&& data->mouse.mouse_x <= b->x + b->width
			&& data->mouse.mouse_y >= b->y
			&& data->mouse.mouse_y <= b->y + b->height)
		{
			data->mouse.button_hovered = i;
			break ;
		}
	}
}

int	handle_mouse_move(int x, int y, t_data *data)
{
	if (!data)
		return (0);
	if (data->current_pg == GAME_PG)
		update_mouse_pos_game(data, x, y);
	else
		update_mouse_pos_menu(data, x, y);
	check_button_hover(data);
	return (0);
}

#endif