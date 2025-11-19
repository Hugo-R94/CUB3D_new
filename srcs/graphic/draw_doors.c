/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:20:40 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/19 12:18:57 by hugz             ###   ########.fr       */
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

void draw_door_column(t_data *data, int value[5], t_img *img, float depth)
{
    t_column_info c;
    int screen_y;
    unsigned int pixel_color;
    int y_offset;
    int index;

    prepare_door_column(&c, value[2], value[3], img);

    y_offset = -(int)(value[2] * data->offset_door_ratio);

    if (y_offset + value[3] < 0)
    {
        c.start_y = -(y_offset + value[3]);
        c.tex_pos = c.start_y * c.step;
    }

    c.y = c.start_y - 1;
    while (++c.y < c.end_y)
    {
        screen_y = value[3] + c.y + y_offset;

        // ✅ Clamp screen_y et value[0] pour rester dans render_gmp
        if (screen_y < 0 || screen_y >= data->render_gmp->height)
            continue;
        if (value[0] < 0 || value[0] >= data->render_gmp->width)
            continue;

        c.tex_y = (int)c.tex_pos;
        if (c.tex_y < 0 || c.tex_y >= img->height)
        {
            c.tex_pos += c.step;
            continue;
        }

        index = value[0] + screen_y * data->render_gmp->width;
        pixel_color = get_pixel(img, value[4], c.tex_y);

        if (pixel_color != 0xFF000000 && pixel_color != 0x000000)
        {
            data->render_gmp->pixels[index].color = pixel_color;
            data->render_gmp->pixels[index].depth = depth;
            data->render_gmp->pixels[index].type = PX_WALL;
        }

        c.tex_pos += c.step;
    }
}
