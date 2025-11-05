/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:17:48 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/04 13:31:09 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS
void	init_data_part1(t_data *data)
{
	data->scale = 3;
	data->map_h = 30;
	data->map_w = 50;
	data->ceiling->width = data->res_x;
	data->ceiling->height = data->res_y;
	data->player_hp = 100;
	data->current_pg = HOME_PG;
	data->current_buttons = g_home_button;
	data->mouse.button_hovered = -1;
	data->game_on = 0;
	data->tilt = 0;
	data->p_is_press = 0;
	data->player.parralax_x = 0;
	data->o_is_press = 0;
	data->fov = M_PI / 3;
	data->in_game = 0;
	data->fps_cap = 30;
	data->a_is_press = 0;
	data->w_is_press = 0;
	data->s_is_press = 0;
	data->d_is_press = 0;
	data->player.rot_speed = (data->res_x * 0.000009375) * 10;
	data->player.mouv_speed = (data->res_x * 0.00003125) * 5;
	data->win_op = 1;
}

t_data	*init_data(void)
{
	t_data	*data;

	data = calloc(1, sizeof(t_data));
	if (!data)
		perror("calloc data");
	data->res_x = 640;
	data->res_y = 480;
	data->win = calloc(1, sizeof(t_win));
	if (!data->win)
		perror("calloc win");
	data->map = calloc(1, sizeof(t_map));
	if (!data->map)
		perror("calloc map");
	create_windows(data->win, data);
	// data->ceiling = calloc(1, sizeof(t_img));
	if (!data->ceiling)
		perror("calloc ceiling");
	data->ceiling = mlx_new_image(data->win->mlx, data->res_x, data->res_y);
	init_data_part1(data);
	if (!data->ceiling)
		perror("mlx_new_image ceiling");
	data->txt = init_textures(data);
	if (!data->txt)
		perror("calloc txt");
	return (data);
}

#else

t_data	*init_data(void)
{
	t_data	*data;

	data = calloc(1, sizeof(t_data));
	if (!data)
	{
		perror("calloc data");
		exit(EXIT_FAILURE);
	}
	data->res_x = 1920;
	data->res_y = 1080;
	data->player.rot_speed = 0.032 * 2;
	data->player.mouv_speed = 0.064 * 2;
	data->a_is_press = 0;
	data->w_is_press = 0;
	data->s_is_press = 0;
	data->d_is_press = 0;
	data->fov = (M_PI / 3);
	data->win = calloc(1, sizeof(t_win));
	if (!data->win)
	{
		perror("calloc win");
		exit(EXIT_FAILURE);
	}
	create_windows(data->win, data);
	return (data);
}

#endif
