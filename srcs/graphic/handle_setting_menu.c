/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_setting_menu.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:43:03 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/30 12:33:54 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS
void	resize_fullscreen(t_data *data);
t_button setting_menu_button[] = {
	{106, 85, 100, 50, "button", resize_640},
	{259, 85, 100, 50, "button", resize_1280},
	{150, 160, 300, 50, "button", resize_fullscreen},
	{412, 85, 100, 50, "button", resize_1920},
	{270, 390, 100, 50, "button", back_to_main},
	{0, 0, 0, 0, NULL, NULL}
};

void	resize_640(t_data *data)
{
	resize_window(data, 640, 480);
}

void	resize_1280(t_data *data)
{
	resize_window(data, 1280, 960);
}

void	resize_1920(t_data *data)
{
	resize_window(data, 1920, 1440);
}

void	resize_fullscreen(t_data *data)
{
	int	screen_w;
	int	screen_h;
	
	mlx_get_screen_size(data->win->mlx, &screen_w, &screen_h);
	resize_window(data, screen_w, screen_h);
}

void	back_to_main(t_data *data)
{
	if (data->in_game == 0)
	{
		data->current_pg = HOME_PG;
		data->current_buttons = g_home_button;
	}
	else
	{
		data->current_pg = PAUSE_PG;
		data->current_buttons = pause_button;
	}
}

void	draw_setting(t_data *data)
{
	data->current_buttons = setting_menu_button;
	draw_to_img(data, "necronomicon", 0, 0);
	draw_rect(data, (int []){75, 30}, (int[]){475, 35}, 0x7D3322);
	put_string_to_img(data, (int []){90, 35}, 0xC73114, "RESOLUTION");
	draw_to_img(data, "button", 106, 85);
	put_string_to_img(data, (int []){112, 97}, 0xC73114, "640");
	// draw_to_img(data, "button", 259, 160);
	draw_rect(data, (int []){150 ,160}, (int []){300 , 50}, 0xFF0000);
	put_string_to_img(data, (int []){170, 175}, 0xC73114, "FULLSCREEN");
	draw_to_img(data, "button", 259, 85);
	put_string_to_img(data, (int []){255, 97}, 0xC73114, "1280");
	draw_to_img(data, "button", 412, 85);
	put_string_to_img(data, (int []){410, 97}, 0xC73114, "1920");
	draw_to_img(data, "button", 270, 390);
	put_string_to_img(data, (int []){272, 402}, 0xC73114, "BACK");
}
#endif