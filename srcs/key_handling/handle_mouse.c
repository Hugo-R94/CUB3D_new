/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:25:16 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/25 14:42:26 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS

static void	scale_mouse_coords(t_data *data, int x, int y, int *scaled)
{
	float	scale[2];

	scale[0] = 640.0f / (float)data->res_x;
	scale[1] = 480.0f / (float)data->res_y;
	scaled[0] = (int)(x * scale[0]);
	scaled[1] = (int)(y * scale[1]);
}

static int	check_button_click(t_data *data, int *mouse_scaled)
{
	int			i;
	t_button	*b;

	i = -1;
	while (data->current_buttons[++i].on_click)
	{
		b = &data->current_buttons[i];
		if (mouse_scaled[0] >= b->x && mouse_scaled[0] <= b->x + b->width
			&& mouse_scaled[1] >= b->y && mouse_scaled[1] <= b->y + b->height)
		{
			if (b->on_click)
				b->on_click(data);
			return (1);
		}
	}
	return (0);
}

int	handle_mouse_click(int button, int x, int y, t_data *data)
{
	int	mouse_scaled[2];

	if (button == 1)
		data->mouse.mouse_button_lc = 1;
	if (button == 3)
		data->mouse.mouse_button_rc = 1;
	if (button != 1)
		return (0);
	scale_mouse_coords(data, x, y, mouse_scaled);
	check_button_click(data, mouse_scaled);
	return (0);
}

int	handle_mouse_press(int button, int x, int y, t_data *data)
{
	if (button == 1)
		data->mouse.mouse_button_lc = 1;
	data->mouse.mouse_x = x;
	data->mouse.mouse_y = y;
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_data *data)
{
	if (button == 1)
		data->mouse.mouse_button_lc = 0;
	if (button == 3)
		data->mouse.mouse_button_rc = 0;
	data->mouse.mouse_x = x;
	data->mouse.mouse_y = y;
	return (0);
}

#endif