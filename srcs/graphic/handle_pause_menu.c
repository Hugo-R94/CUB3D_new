/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pause_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:31:16 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/21 15:31:52 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#ifdef BONUS
void	resume(t_data *data);
void	go_main_menu(t_data *data);

t_button pause_button[] = 
{
	{170, 150, 300, 75, "button", resume},
	{170, 255, 300, 75, "button", go_setting_menu},
	{170, 360, 300, 75, "button MENU", go_main_menu},
	{0, 0, 0, 0, NULL, NULL}
};

void	resume(t_data *data)
{
	data->current_pg = GAME_PG;
}

void	go_main_menu(t_data *data)
{
	data->current_pg = HOME_PG;
	data->current_buttons = g_home_button;
}

void	darken_image(t_img *img, float factor)
{
	int			x;
	int			y;
	uint8_t		can[3];
	uint32_t	color[2];

	if (!img || !img->data)
		return ;
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
		{
			color[0] = get_pixel(img, x, y);
			can[0] = (color[0] >> 16) & 0xFF;
			can[1] = (color[0] >> 8) & 0xFF;
			can[2] = color[0] & 0xFF;
			can[0] *= factor;
			can[1] *= factor;
			can[2] *= factor;
			color[1] = (can[0] << 16) | (can[1] << 8) | can[2];
			put_pixel(img, x, y, color[1]);
		}
	}
}

void	draw_pause_menu(t_data *data)
{
	
	put_string_to_img(data, (int []){195, 100}, 0xFF0000, "PAUSE MENU");
	draw_rect(data, (int []){170, 150}, (int []){300, 75}, 0xFF0000);
	put_string_to_img(data, (int []){245, 175}, 0xFF0000, "RESUME");
	put_string_to_img(data, (int []){235, 280}, 0xFF0000, "SETTING");
	put_string_to_img(data, (int []){225, 385}, 0xFF0000, "MAIN MENU");
	draw_rect(data, (int []){170, 255}, (int []){300, 75}, 0xFF0000);
	draw_rect(data, (int []){170, 360}, (int []){300, 75}, 0xFF0000);
}
#endif