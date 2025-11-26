/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:07:11 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 15:11:23 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	draw_hud_background(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < 600)
	{
		y = 0;
		while (y < 200)
		{
			put_pixel(data->win->img, x, y, 0xF421E9);
			y++;
		}
		x++;
	}
}

void	draw_hud(t_data *data)
{
	draw_hud_background(data);
	draw_to_img(data, "test", 0, 0);
	draw_to_img(data, "HUD_placeholder", 0, 0);
}

void	draw_mouse_icon(t_data *data)
{
	if (data->current_pg != GAME_PG)
		draw_to_img(data, "pointeur", data->mouse.mouse_x, data->mouse.mouse_y);
}

void	render_home_pages(t_data *data)
{
	if (data->current_pg == HOME_PG)
		draw_home_page(data);
	else if (data->current_pg == GMP_PG)
		draw_game_mode(data);
	else if (data->current_pg == SETT_PG)
		draw_setting(data);
	else if (data->current_pg == DEATH_PG)
		draw_death_menu(data);
	else if (data->current_pg == WIN_PG)
		draw_win_screen(data);
}

#endif