/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_render_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:43:49 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/13 17:14:01 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

#include <math.h>
#include <stdint.h>
static inline uint32_t blend50(uint32_t under, uint32_t over)
{
    uint8_t r1 = (under >> 16) & 0xFF;
    uint8_t g1 = (under >> 8) & 0xFF;
    uint8_t b1 = under & 0xFF;

    uint8_t r2 = (over >> 16) & 0xFF;
    uint8_t g2 = (over >> 8) & 0xFF;
    uint8_t b2 = over & 0xFF;

    // Blend 50% (simple moyenne)
    uint8_t r = (r1 + r2) / 2;
    uint8_t g = (g1 + g2) / 2;
    uint8_t b = (b1 + b2) / 2;

    return (r << 16) | (g << 8) | b;
}

void draw_parallax_layer(t_data *data, t_img *dest, t_txt *layer, float factor, int offset[2])
{
    int x, y;
    int tex_x, tex_y;
    int offset_x, offset_y;
    uint32_t color, base_color;

    offset_x = ((int)(data->player.parralax_x * 1.81 * 2) + (int)(data->player.px * 5)) * factor + offset[0];
    offset_y = (int)(((data->tilt + data->player.py) * (-factor) )) - 600 - offset[1];

    y = 0;
    while (y < dest->height)
    {
        x = 0;
        while (x < dest->width)
        {
            tex_x = (x + offset_x) % layer->img.width;
            tex_y = (y + offset_y) % layer->img.height;

            if (tex_x < 0)
                tex_x += layer->img.width;
            if (tex_y < 0)
                tex_y += layer->img.height;

            color = get_pixel(&layer->img, tex_x, tex_y);

            if (color != 0x000000)
            {
                // Récupère le pixel déjà présent
                base_color = get_pixel(dest, x, y);

                // Blend uniquement si base_color != 0 (donc pas le premier layer)
                if (base_color != 0x000000)
                    color = blend50(base_color, color);
                put_pixel(dest, x, y, color);
            }
            x++;
        }
        y++;
    }
}

void    draw_ceiling_img(t_data *data)
{
    t_txt *texture;

    texture = find_texture(data->txt, "skybox");
    if (texture)
    {
        draw_parallax_layer(data, data->ceiling, texture, 1.0f, (int []){0, 0});
    }
    texture = find_texture(data->txt, "cloud_1");
    if (texture)
    {
        draw_parallax_layer(data, data->ceiling, texture, 1.2f, (int []){2456, 0});
        draw_parallax_layer(data, data->ceiling, texture, 1.35f, (int []){323, 25});
        draw_parallax_layer(data, data->ceiling, texture, 1.6f, (int []){-4342, 50});
        draw_parallax_layer(data, data->ceiling, texture, 1.8f, (int []){-233, 75});
    }
}


/* --- Ancien draw_ceiling, version "render_gmp" --- */
void	draw_ceiling(t_data *data, int x, int y_end, t_img *ceiling)
{
	int			y;
	int			tex_x;
	int			tex_y;
	uint32_t	color;
	int			index;

	if (!ceiling || !ceiling->data)
		return;
	y = 0;
	while (y < y_end)
	{
		tex_x = x % ceiling->width;
		tex_y = y % ceiling->height;
		if (tex_x < 0)
			tex_x += ceiling->width;
		if (tex_y < 0)
			tex_y += ceiling->height;
		color = get_pixel(ceiling, tex_x, tex_y);
		if (color != 0x000000)
		{
			index = y * data->render_gmp->width + x;
			// profondeur négative (infini haut) pour éviter d’écraser murs/plancher
			data->render_gmp->pixels[index].color = color;
			data->render_gmp->pixels[index].depth = -1;
			data->render_gmp->pixels[index].type = PX_EMPTY;
		}
		y++;
	}
}

#endif