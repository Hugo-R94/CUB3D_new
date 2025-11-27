/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_column_draw_mand.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:53:53 by hugz              #+#    #+#             */
/*   Updated: 2025/11/27 12:00:13 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifndef BONUS

void	put_wall_pixel(t_data *data, t_img *img, int i[3], float tex_pos)
{
	int		tex_y;
	int		color;

	tex_y = (int)tex_pos;
	color = get_pixel(img, i[2], tex_y);
	put_pixel(data->win->img, i[0], i[1], color);
}

void	draw_ceiling(t_data *data, int x, int start_y, int end_y)
{
	int	current_y;

	current_y = start_y;
	while (current_y < end_y)
	{
		put_pixel(data->win->img, x, current_y, data->map->c_color);
		current_y++;
	}
}

void	draw_floor(t_data *data, int x, int start_y)
{
	int	current_y;

	current_y = start_y;
	while (current_y < data->res_y)
	{
		put_pixel(data->win->img, x, current_y, data->map->f_color);
		current_y++;
	}
}

void	render_column(t_data *data, t_img *img, int x[2], int full_line_h)
{
	int		line_off;
	int		y;
	int		y_end;
	float	tex_pos;
	float	step;

	step = (float)img->height / full_line_h;
	line_off = get_line_offset(data, full_line_h);
	tex_pos = get_initial_tex_pos(line_off, step);
	y = get_start_y(line_off);
	y_end = get_end_y(data, line_off, full_line_h);
	draw_ceiling(data, x[0], 0, y);
	while (y < y_end)
	{
		put_wall_pixel(data, img, (int []){x[0], y, x[1]}, tex_pos);
		tex_pos += step;
		y++;
	}
	draw_floor(data, x[0], y_end);
}

#endif