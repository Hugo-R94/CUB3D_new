/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_setting_menu.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:43:03 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/28 12:56:09 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS

void	set_fov(t_data *data);
void	resize_fullscreen(t_data *data);
void	set_sensi(t_data *data);

t_button	g_setting_menu_button[]
	= {
{106, 85, 100, 50, "button", resize_640},
{259, 85, 100, 50, "button", resize_1280},
{150, 160, 300, 50, "button", resize_fullscreen},
{412, 85, 100, 50, "button", resize_1920},
{270, 390, 100, 50, "button", back_to_main},
{385, 282, 25, 25, "slider_button_fov", set_fov},
{385, 345, 25, 25, "slider_button_sensi", set_sensi},
{0, 0, 0, 0, NULL, NULL}
};

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
		data->current_buttons = g_pause_button;
	}
}

void	choose_res(t_data *data)
{
	draw_rect(data, (int []){75, 30}, (int []){475, 35}, 0x7D3322);
	put_string_to_img(data, (int []){90, 35}, 0xC73114, "RESOLUTION");
	draw_to_img(data, "button", 106, 85);
	put_string_to_img(data, (int []){112, 97}, 0xC73114, "640");
	draw_rect(data, (int []){150, 160}, (int []){300, 50}, 0xFF0000);
	put_string_to_img(data, (int []){170, 175}, 0xC73114, "FULLSCREEN");
	draw_to_img(data, "button", 259, 85);
	put_string_to_img(data, (int []){255, 97}, 0xC73114, "1280");
	draw_to_img(data, "button", 412, 85);
	put_string_to_img(data, (int []){410, 97}, 0xC73114, "1920");
}

void	choose_fov(t_data *data)
{
	char	*fov;

	put_string_to_img(data, (int []){90, 225}, 0xC73114, "OTHERS  ");
	draw_rect(data, (int []){75, 270}, (int []){150, 50}, 0xFF0000);
	put_string_to_img(data, (int []){110, 280}, 0xC73114, "FOV");
	draw_rect_fill(data, (int []){246, 286},
		(int []){g_setting_menu_button[5].x - 240, 15}, 0xFF0000);
	draw_to_img(data, "slider_base", 245, 285);
	draw_to_img(data, "slider_button", g_setting_menu_button[5].x,
		g_setting_menu_button[5].y);
	if (data->mouse.mouse_button_lc && data->slider_button1)
		g_setting_menu_button[5].x = data->mouse.mouse_x;
	if (g_setting_menu_button[5].x < 250)
		g_setting_menu_button[5].x = 250;
	if (g_setting_menu_button[5].x > 520)
		g_setting_menu_button[5].x = 520;
	if (data->mouse.mouse_button_lc == 0)
		data->slider_button1 = 0;
	data->fov = (M_PI / 3) * ((float)g_setting_menu_button[5].x / 333);
	fov = ft_itoa(data->fov / 0.01415 + 5);
	put_string_to_img(data, (int []){550, 280}, 0xFF0000, fov);
}

void	choose_sensi(t_data *data)
{
	char	*sensi;

	draw_rect(data, (int []){75, 330}, (int []){150, 50}, 0xFF0000);
	put_string_to_img(data, (int []){90, 340}, 0xC73114, "SENSI");
	draw_rect_fill(data, (int []){246, 345},
		(int []){g_setting_menu_button[6].x - 240, 15}, 0xFF0000);
	draw_to_img(data, "slider_base", 245, 345);
	draw_to_img(data, "slider_button",
		g_setting_menu_button[6].x, g_setting_menu_button[6].y);
	if (data->mouse.mouse_button_lc && data->slider_button2)
		g_setting_menu_button[6].x = data->mouse.mouse_x;
	if (g_setting_menu_button[6].x < 250)
		g_setting_menu_button[6].x = 250;
	if (g_setting_menu_button[6].x > 520)
		g_setting_menu_button[6].x = 520;
	if (data->mouse.mouse_button_lc == 0)
		data->slider_button2 = 0;
	data->mouse.sensitivity = 0.000003
		* ((float)g_setting_menu_button[6].x / 2.7 - 92.59) + 0.0002;
	sensi = ft_itoa((float)g_setting_menu_button[6].x / 2.7 - 92.59);
	if (data->mouse.sensitivity <= 0.00021)
		put_string_to_img(data, (int []){550, 345}, 0xFF0000, "1");
	else
		put_string_to_img(data, (int []){550, 345}, 0xFF0000, sensi);
	free(sensi);
}

void	draw_setting(t_data *data)
{
	data->current_buttons = g_setting_menu_button;
	draw_to_img(data, "necronomicon", 0, 0);
	choose_res(data);
	choose_fov(data);
	choose_sensi(data);
	draw_to_img(data, "button", 270, 390);
	put_string_to_img(data, (int []){272, 402}, 0xC73114, "BACK");
}

#endif