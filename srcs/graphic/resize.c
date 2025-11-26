/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:10:15 by hugz              #+#    #+#             */
/*   Updated: 2025/11/26 17:11:32 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS

void	resize_window(t_data *data, int resx, int resy)
{
	if (data->res_x == resx && data->res_y == resy)
	{
		printf("la taille ne change pas \n");
		return ;
	}
	if (data->win->img)
	{
		mlx_destroy_image(data->win->mlx, data->win->img);
		data->win->img = NULL;
	}
	if (data->win->win)
	{
		mlx_destroy_window(data->win->mlx, data->win->win);
		data->win->win = NULL;
	}
	data->res_x = resx;
	data->res_y = resy;
	data->win->win = mlx_new_window(data->win->mlx,
			data->res_x, data->res_y, "EVIL DOOM");
	data->win->img = mlx_new_image(data->win->mlx, data->res_x, data->res_y);
	mlx_game_loop(data);
}

#endif