/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:58:53 by hugz              #+#    #+#             */
/*   Updated: 2025/11/27 13:59:36 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

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

#endif