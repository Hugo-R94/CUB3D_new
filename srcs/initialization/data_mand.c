/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_mand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:25:21 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 13:25:47 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifndef BONUS

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