/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_column_mand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:53:34 by hugz              #+#    #+#             */
/*   Updated: 2025/11/27 11:57:58 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifndef BONUS

int	get_line_offset(t_data *data, int full_line_h)
{
	int	line_off;

	line_off = (data->res_y - full_line_h) / 2;
	return (line_off);
}

float	get_initial_tex_pos(int line_off, float step)
{
	float	tex_pos;

	if (line_off < 0)
		tex_pos = (-line_off) * step;
	else
		tex_pos = 0.0f;
	return (tex_pos);
}

int	get_start_y(int line_off)
{
	int	y;

	if (line_off < 0)
		y = 0;
	else
		y = line_off;
	return (y);
}

int	get_end_y(t_data *data, int line_off, int full_line_h)
{
	int	y_end;

	y_end = line_off + full_line_h;
	if (y_end > data->res_y)
		y_end = data->res_y;
	return (y_end);
}

#endif