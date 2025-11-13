/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:34:38 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/13 17:25:43 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/time.h>
#include <unistd.h>

#ifdef BONUS

static long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static void	draw_hud_background(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < 600)
	{
		y = 0;
		while (y < 200)
		{
			put_pixel(data->win->img, x, y, 0xF421E9);
			y++;
		}
		x++;
	}
}

void	draw_hud(t_data *data)
{
	draw_hud_background(data);
	draw_to_img(data, "test", 0, 0);
	draw_to_img(data, "HUD_placeholder", 0, 0);
}

void	draw_mouse_icon(t_data *data)
{
	if (data->current_pg != GAME_PG)
		draw_to_img(data, "pointeur", data->mouse.mouse_x, data->mouse.mouse_y);
}

static void	render_home_pages(t_data *data)
{
	if (data->current_pg == HOME_PG)
		draw_home_page(data);
	else if (data->current_pg == GMP_PG)
		draw_game_mode(data);
	else if (data->current_pg == SETT_PG)
		draw_setting(data);
}

static void	render_pause(t_data *data)
{
	render_gameplay_full(data);
	data->game_on = 0;
	data->current_buttons = pause_button;
	darken_image(data->win->img, 0.5f);
	draw_pause_menu(data);
}

void	render_img(t_data *data)
{
	if (data->current_pg == GAME_PG)
		render_gameplay_full(data);
	else if (data->current_pg == PAUSE_PG)
		render_pause(data);	
	else
		render_home_pages(data);
}

static int	is_valid_render_data(t_data *data)
{
	if (!data || !data->win)
		return (0);
	if (!data->win->mlx || !data->win->win || !data->win->img)
		return (0);
	return (1);
}

static void	clear_frame(t_data *data)
{
	ft_memset(data->win->img->data, 0,
		data->win->img->height * data->win->img->size_line);
}

static void	highlight_hovered_button(t_data *data)
{
	t_button	*btn;

	if (data->mouse.button_hovered != -1)
	{
		btn = &data->current_buttons[data->mouse.button_hovered];
		highlight_button(data, btn);
	}
}

static void	calculate_fps(long *prev, float *fps, long current)
{
	if (*prev != 0)
		*fps = 1000.0f / (current - *prev);
	*prev = current;
}

static void	cap_framerate(t_data *data, long elapsed)
{
	long	target_time;

	target_time = 1000 / data->fps_cap;
	if (elapsed < target_time)
		usleep((target_time - elapsed) * 1000);
}

static void	render_scene(t_data *data)
{
	clear_frame(data);
	render_img(data);
	highlight_hovered_button(data);
	draw_mouse_icon(data);
	upscale(data);
	if (data->res_x == data->win->img->width && data->res_y == data->win->img->height)
		mlx_put_image_to_window(data->win->mlx, data->win->win,
			data->win->img, 0, 0);
	else
		mlx_put_image_to_window(data->win->mlx, data->win->win,
			data->win->img, ((data->res_x / 2) - (data->win->img->width / 2)),
			(((data->res_y / 2) - data->win->img->height / 2)) / 2);
	// if (data->ceiling->data && data->current_pg == GAME_PG)
	// 	copy_texture_to_img(data->ceiling, data->win->img, 0,0);
	// else
	// 	printf("ceilling image existe pas");
}

void print_p_data(t_data *data)
{
    // Remonte de 2 lignes
    printf("\033[3A");
    // Efface la ligne actuelle et réécrit la première valeur
    printf("\rplayer angle = %.2f\n", data->player.pa);
    // Efface la ligne suivante et réécrit la deuxième valeur
    printf("player speed = %.2f\n", data->player.mouv_speed);
	printf("mouse position = %dx%d\n",data->mouse.mouse_x, data->mouse.mouse_y);
    fflush(stdout);
}
int	render_frame(t_data *data)
{
	static long		prev_time = 0;
	static float	fps = 0;
	long			times[2];
	char *fps_str;
	if (!is_valid_render_data(data))
		return (0);
	times[0] = get_time_ms();
	render_scene(data);
	times[1] = get_time_ms();
	fps_str = ft_itoa(fps);
	mlx_string_put(data->win->mlx,data->win->win,50,50, 0xFF0000, fps_str);
	free(fps_str);
	// print_p_data(data);
	data->timer +=1;
	if (data->timer >= 300)
	{
		print_map(data->map->map);
		data->timer = 0;
	}
	calculate_fps(&prev_time, &fps, times[1]);
	cap_framerate(data, times[1] - times[0]);
	handle_key_game(data);
	return (0);
}

static void	setup_hooks(t_data *data)
{
	mlx_loop_hook(data->win->mlx, render_frame, data);
	mlx_hook(data->win->win, 2, 1L << 0, handle_key, data);
	mlx_hook(data->win->win, 17, 0, handle_close, data);
	mlx_hook(data->win->win, 4, 1L<<2, handle_mouse_press, data);
	mlx_hook(data->win->win, 5, 1L<<3, handle_mouse_release, data);
	mlx_mouse_hook(data->win->win, handle_mouse_click, data);
	mlx_hook(data->win->win, 2, 1L << 0, handle_key_press, data);
	mlx_hook(data->win->win, 3, 1L << 1, handle_key_release, data);
	mlx_hook(data->win->win, 6, 1L << 6, handle_mouse_move, data);
}

void	mlx_game_loop(t_data *data)
{
	setup_hooks(data);
	mlx_mouse_hide(data->win->mlx, data->win->win);
	mlx_loop(data->win->mlx);
}

#endif