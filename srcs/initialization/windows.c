/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:58:32 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/05 12:53:58 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void create_windows(t_win *win, t_data *data)
{
	win->mlx = mlx_init();
	if (!win->mlx)
	{
		perror("mlx_init error");
		exit(1);
	}

	win->win = mlx_new_window(win->mlx, data->res_x, data->res_y, "EVIL DOOM");
	if (!win->win)
	{
		perror("mlx_new_window error");
		exit(1);
	}

	win->img = mlx_new_image(win->mlx, data->res_x, data->res_y);
	if (!win->img)
	{
		perror("mlx_new_image error");
		exit(1);
	}
	// printf("✅ MLX initialized: mlx=%p, win=%p, img=%p\n", win->mlx, win->win, win->img);
}
