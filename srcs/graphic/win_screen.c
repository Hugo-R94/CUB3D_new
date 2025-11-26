/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:19:27 by hugz              #+#    #+#             */
/*   Updated: 2025/11/26 17:24:53 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

t_button	g_win_screen[]
	= {
{214, 125, 213, 75, "retry", retry_game},
{214, 225, 213, 75, "menu", play_mainmenu},
{214, 325, 213, 75, "exit", clear_and_exit},
{0, 0, 0, 0, NULL, NULL}
};

void	draw_win_screen(t_data *data)
{
	render_gameplay_full(data);
	data->game_on = 0;
	darken_image(data->win->img, 0.65f);
	data->current_buttons = g_win_screen;
	put_string_to_img(data, (int []){245, 75}, 0xFF0000, "YOU WIN");
	put_string_to_img(data, (int []){260, 150}, 0xFF0000, "RETRY");
	draw_rect(data, (int []){214, 125}, (int []){213, 75}, 0xFF0000);
	put_string_to_img(data, (int []){270, 250}, 0xFF0000, "MENU");
	draw_rect(data, (int []){214, 225}, (int []){213, 75}, 0xFF0000);
	put_string_to_img(data, (int []){270, 350}, 0xFF0000, "EXIT");
	draw_rect(data, (int []){214, 325}, (int []){213, 75}, 0xFF0000);
}

#endif