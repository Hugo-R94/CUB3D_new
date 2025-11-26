/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:07:46 by hugz              #+#    #+#             */
/*   Updated: 2025/11/26 12:26:22 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

void	render_pause(t_data *data)
{
	render_gameplay_full(data);
	data->game_on = 0;
	data->current_buttons = g_pause_button;
	darken_image(data->win->img, 0.5f);
	draw_pause_menu(data);
}

void	render_img(t_data *data)
{
	if (data->current_pg == GAME_PG)
		render_gameplay_full(data);
	else if (data->current_pg == PAUSE_PG)
		render_pause(data);
	else
		render_home_pages(data);
}

int	is_valid_render_data(t_data *data)
{
	if (!data || !data->win)
		return (0);
	if (!data->win->mlx || !data->win->win || !data->win->img)
		return (0);
	return (1);
}

void	clear_frame(t_data *data)
{
	ft_memset(data->win->img->data, 0,
		data->win->img->height * data->win->img->size_line);
}

void	highlight_hovered_button(t_data *data)
{
	t_button	*btn;

	if (data->mouse.button_hovered != -1)
	{
		btn = &data->current_buttons[data->mouse.button_hovered];
		highlight_button(data, btn);
	}
}

#endif