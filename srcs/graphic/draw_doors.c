/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:20:40 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/04 17:15:19 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* --- Étape 1 : Préparer les données de colonne pour porte --- */
static void prepare_door_column(t_column_info *c, int line_h, int line_off, t_img *img)
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

/* --- Étape 2 : Dessiner la colonne de porte --- */
void draw_door_column(t_data *data, int value[5], t_img *img, int depth)
{
    t_column_info   c;
    int             screen_y;
    unsigned int    pixel_color;

	    // DEBUG
    // printf("=== DOOR COLUMN DEBUG ===\n");
    // printf("img = %p\n", img);
    // printf("img->data = %p\n", img->data);
    // printf("img->width = %d, height = %d\n", img->width, img->height);
    // printf("tex_x = %d\n", value[4]);
    prepare_door_column(&c, value[2], value[3], img);
    c.y = c.start_y - 1;
    while (++c.y < c.end_y)
    {
        screen_y = value[3] + c.y;
        if (screen_y >= 0 && screen_y < c.screen_h)
        {
            c.tex_y = (int)c.tex_pos;
            if (c.tex_y >= img->height)
                c.tex_y = img->height - 1;
            pixel_color = get_pixel(img, value[4], c.tex_y);
			// printf("color = %d", c.color);
            if (pixel_color != 0xFF000000)
            {
                c.color = depth_render(pixel_color, depth);
				// c.color = 0xFF0000;
                if (c.color != 0x000000)
                    put_pixel(data->win->img, value[0], screen_y, c.color);
            }
        }
        c.tex_pos += c.step;
    }
}