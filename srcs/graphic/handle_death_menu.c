/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_death_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:11:12 by hugz              #+#    #+#             */
/*   Updated: 2025/11/24 15:50:30 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS 
void retry_game(t_data *data);

t_button	g_death_menu[] =
{
	{214 , 125, 213, 75, "retry", retry_game},
	{214 , 225, 213, 75, "menu", play_mainmenu},
	{214 , 325, 213, 75, "exit", clear_and_exit},
	{0, 0, 0, 0, NULL, NULL}
};




void	draw_death_menu(t_data	*data)
{
	render_gameplay_full(data);
	data->game_on = 0;
	darken_image(data->win->img, 0.65f);
	data->current_buttons = g_death_menu;
	put_string_to_img(data, (int []){220, 75}, 0xFF0000, "YOU DEAD");
	put_string_to_img(data, (int []){260, 150}, 0xFF0000, "RETRY");
	draw_rect(data, (int []){214, 125}, (int []){213, 75}, 0xFF0000);
	put_string_to_img(data, (int []){270, 250}, 0xFF0000, "MENU");
	draw_rect(data, (int []){214, 225}, (int []){213, 75}, 0xFF0000);
	put_string_to_img(data, (int []){270, 350}, 0xFF0000, "EXIT");
	draw_rect(data, (int []){214, 325}, (int []){213, 75}, 0xFF0000);
}

#endif