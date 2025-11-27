/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:20:40 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/27 13:31:52 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

static void	init_column_info(t_column_info *c, int line_h, t_img *img)
{
	c->screen_h = 480;
	c->line_h = line_h;
	c->step = (float)img->height / line_h;
	c->tex_pos = 0.0f;
	c->start_y = 0;
	c->end_y = line_h;
}

static void	adjust_column_bounds(t_column_info *c, int line_off)
{
	if (line_off < 0)
	{
		c->start_y = -line_off;
		c->tex_pos = c->start_y * c->step;
	}
	if (line_off + c->line_h > c->screen_h)
		c->end_y = c->screen_h - line_off;
}

static void	prepare_door_column(t_column_info *c,
		int line_h, int line_off, t_img *img)
{
	init_column_info(c, line_h, img);
	adjust_column_bounds(c, line_off);
}

static void	adjust_door_offset(t_column_info *c, int value[5], t_data *data)
{
	int	y_offset;

	y_offset = -(int)(value[2] * data->offset_door_ratio);
	if (y_offset + value[3] < 0)
	{
		c->start_y = -(y_offset + value[3]);
		c->tex_pos = c->start_y * c->step;
	}
}

//y_inf[0] = screen_y y_inf[1] = tex_y
static int	should_skip_pixel(t_data *data, int value[5],
		int y_inf[2], t_img *img)
{
	if (y_inf[0] < 0 || y_inf[0] >= data->render_gmp->height)
		return (1);
	if (value[0] < 0 || value[0] >= data->render_gmp->width)
		return (1);
	if (y_inf[1] < 0 || y_inf[1] >= img->height)
		return (1);
	return (0);
}

//int col_i[0] = colors col_i[1] = index 
static void	draw_pixel_if_valid(t_data *data,
		unsigned int col_i[2], float depth)
{
	if (col_i[0] != 0xFF000000 && col_i[0] != 0x000000)
	{
		data->render_gmp->pixels[col_i[1]].color = col_i[0];
		data->render_gmp->pixels[col_i[1]].depth = depth;
		data->render_gmp->pixels[col_i[1]].type = PX_WALL;
	}
}

void	draw_door_column(t_data *data, int value[5], t_img *img, float depth)
{
	t_column_info	c;
	int				screen_y;
	unsigned int	pixel_color;
	int				y_offset;
	int				index;

	prepare_door_column(&c, value[2], value[3], img);
	adjust_door_offset(&c, value, data);
	y_offset = -(int)(value[2] * data->offset_door_ratio);
	c.y = c.start_y - 1;
	while (++c.y < c.end_y)
	{
		screen_y = value[3] + c.y + y_offset;
		c.tex_y = (int)c.tex_pos;
		if (should_skip_pixel(data, value, (int []){screen_y, c.tex_y}, img))
		{
			c.tex_pos += c.step;
			continue ;
		}
		index = value[0] + screen_y * data->render_gmp->width;
		pixel_color = get_pixel(img, value[4], c.tex_y);
		draw_pixel_if_valid(data,
			(unsigned int []){pixel_color, index}, depth);
		c.tex_pos += c.step;
	}
}

#endif