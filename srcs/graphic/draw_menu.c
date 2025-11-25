/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:50:03 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/21 15:47:32 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS

t_button	g_home_button[] = {
{341, 195, 195, 60, "button", go_play_menu},
{341, 269, 195, 60, "setting", go_setting_menu},
{341, 338, 195, 60, "exit", clear_and_exit},
{0, 0, 0, 0, NULL, NULL}
};

void	go_play_menu(t_data *data)
{
	data->current_pg = GMP_PG;
	data->current_buttons = gmd_selector;
}

void	go_setting_menu(t_data *data)
{
	data->current_pg = SETT_PG;
}

void	draw_home_page(t_data *data)
{
	int	pos[2];

	pos[0] = 25;
	pos[1] = 25;
	draw_to_img(data, "Home_bg", 0, 0);
	draw_to_img(data, "Home_ash", 0, 0);
	draw_to_img(data, "Home_title", 0, 0);
}
#endif