/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:48:18 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/04 14:17:04 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS


/* --- Étape 1 : Préparer les données de colonne --- */
static void prepare_wall_column(t_column_info *c, int line_h, int line_off, t_img *img)
{
	c->screen_h = 480;
	c->line_h = line_h;
	c->step = (float)img->height / line_h;
	c->tex_pos = 0.0f;

	c->start_y = 0;
	c->end_y = line_h;

	if (line_off < 0)
	{
		c->start_y = -line_off;
		c->tex_pos = c->start_y * c->step;
	}
	if (line_off + line_h > c->screen_h)
		c->end_y = c->screen_h - line_off;
}

/* --- Étape 2 : Dessiner la colonne --- */
void draw_wall_column(t_data *data, int value[5], t_img *img, int depth)
{
	t_column_info	c;
	int 		screen_y;
	prepare_wall_column(&c, value[2], value[3], img);

	for (c.y = c.start_y; c.y < c.end_y; c.y++)
	{
		screen_y = value[3] + c.y;

		if (screen_y >= 0 && screen_y < c.screen_h)
		{
			c.tex_y = (int)c.tex_pos;
			if (c.tex_y >= img->height)
				c.tex_y = img->height - 1;

			c.color = depth_render(get_pixel(img, value[4], c.tex_y), depth);
			if (c.color != 0x000000)
				put_pixel(data->win->img, value[0], screen_y, c.color);
		}
		c.tex_pos += c.step;
	}
}


#endif