/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:34:38 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/28 12:54:36 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/time.h>
#include <unistd.h>

#ifdef BONUS

void	cap_framerate(t_data *data, long elapsed)
{
	long	target_time;

	target_time = 1000 / data->fps_cap;
	if (elapsed < target_time)
		usleep((target_time - elapsed) * 1000);
}

void	render_scene(t_data *data)
{
	clear_frame(data);
	render_img(data);
	highlight_hovered_button(data);
	draw_mouse_icon(data);
	upscale(data);
	if (data->res_x == data->win->img->width
		&& data->res_y == data->win->img->height)
		mlx_put_image_to_window(data->win->mlx, data->win->win,
			data->win->img, 0, 0);
	else
		mlx_put_image_to_window(data->win->mlx, data->win->win,
			data->win->img, ((data->res_x / 2) - (data->win->img->width / 2)),
			(((data->res_y / 2) - data->win->img->height / 2)) / 2);
}

int	render_frame(t_data *data)
{
	static long		prev_time = 0;
	static float	fps = 0;
	long			times[2];
	char			*fps_str;

	if (!is_valid_render_data(data))
		return (0);
	times[0] = get_time_ms();
	render_scene(data);
	times[1] = get_time_ms();
	fps_str = ft_itoa(fps);
	mlx_string_put(data->win->mlx, data->win->win, 50, 50, 0xFF0000, fps_str);
	free(fps_str);
	calculate_fps(&prev_time, &fps, times[1]);
	cap_framerate(data, times[1] - times[0]);
	handle_key_game(data);
	return (0);
}

void	setup_hooks(t_data *data)
{
	mlx_loop_hook(data->win->mlx, render_frame, data);
	mlx_hook(data->win->win, 17, 0, handle_close, data);
	mlx_hook(data->win->win, 5, 1L << 3, handle_mouse_release, data);
	mlx_mouse_hook(data->win->win, handle_mouse_click, data);
	mlx_hook(data->win->win, 2, 1L << 0, handle_key_press, data);
	mlx_hook(data->win->win, 3, 1L << 1, handle_key_release, data);
	mlx_hook(data->win->win, 6, 1L << 6, handle_mouse_move, data);
}

// mlx_mouse_hide(data->win->mlx, data->win->win);
void	mlx_game_loop(t_data *data)
{
	setup_hooks(data);
	mlx_mouse_hide(data->win->mlx, data->win->win);
	mlx_loop(data->win->mlx);
}

#endif