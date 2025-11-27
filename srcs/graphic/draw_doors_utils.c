/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_doors_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:56:03 by hugz              #+#    #+#             */
/*   Updated: 2025/11/27 13:57:33 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

void	init_column_info(t_column_info *c, int line_h, t_img *img)
{
	c->screen_h = 480;
	c->line_h = line_h;
	c->step = (float)img->height / line_h;
	c->tex_pos = 0.0f;
	c->start_y = 0;
	c->end_y = line_h;
}

void	adjust_column_bounds(t_column_info *c, int line_off)
{
	if (line_off < 0)
	{
		c->start_y = -line_off;
		c->tex_pos = c->start_y * c->step;
	}
	if (line_off + c->line_h > c->screen_h)
		c->end_y = c->screen_h - line_off;
}

void	prepare_door_column(t_column_info *c,
		int line_h, int line_off, t_img *img)
{
	init_column_info(c, line_h, img);
	adjust_column_bounds(c, line_off);
}

void	adjust_door_offset(t_column_info *c, int value[5], t_data *data)
{
	int	y_offset;

	y_offset = -(int)(value[2] * data->offset_door_ratio);
	if (y_offset + value[3] < 0)
	{
		c->start_y = -(y_offset + value[3]);
		c->tex_pos = c->start_y * c->step;
	}
}

#endif