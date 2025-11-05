/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_render_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:43:49 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/03 13:51:57 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

#include <math.h>
#include <stdint.h>

// Applique un plan de parallaxe dans une image cible
void draw_parallax_layer(t_data *data, t_img *dest, t_txt *layer, float factor)
{
    int x, y;
    int tex_x, tex_y;
    int offset_x, offset_y;
    uint32_t color, base;
    uint8_t r, g, b;

	
    // Calcul des offsets en entiers
    offset_x = (int)(((-data->player.px / 5) + data->player.parralax_x) * factor * 100); // Multiplier pour avoir un effet visible
    offset_y = (int)(data->tilt * - factor * 10) - 600;

    y = 0;
    while (y < dest->height)
    {
        x = 0;
        while (x < dest->width)
        {
            // Décalage selon la rotation (pa) et l'inclinaison (tilt)
            tex_x = (x + offset_x) % layer->img.width;
            tex_y = (y + offset_y) % layer->img.height;
            
            // Gérer les valeurs négatives du modulo
            if (tex_x < 0)
                tex_x += layer->img.width;
            if (tex_y < 0)
                tex_y += layer->img.height;
            
            color = get_pixel(&layer->img, tex_x, tex_y);
            
            // Blend additif avec le fond existant
            base = get_pixel(dest, x, y);
            r = ((base >> 16 & 0xFF) + (color >> 16 & 0xFF)) / 2;
            g = ((base >> 8 & 0xFF) + (color >> 8 & 0xFF)) / 2;
            b = ((base & 0xFF) + (color & 0xFF)) / 2;
            put_pixel(dest, x, y, (r << 16) | (g << 8) | b);
            
            x++;
        }
        y++;
    }
}

void    draw_ceiling_img(t_data *data)
{
    t_txt *texture;

    // Layer 1
    texture = find_texture(data->txt, "skybox");
    if (texture)
        draw_parallax_layer(data, data->ceiling, texture, 0.1f);
    
    // Layer 2
    texture = find_texture(data->txt, "cloud");
    if (texture)
        draw_parallax_layer(data, data->ceiling, texture, 0.15f);
    
    // // Layer 3
    // texture = find_texture(data->txt, "Ash_25");
    // if (texture)
    //     draw_parallax_layer(data, data->ceiling, texture, 0.7f);
    
    // // Layer 4
    // texture = find_texture(data->txt, "E");
    // if (texture)
    //     draw_parallax_layer(data, data->ceiling, texture, 0.5f);
}


// void draw_ceiling_to_screen(t_data *data)
// {
// 	for (int y = 0; y < data->res_y / 2; y++)
// 	{
// 		for (int x = 0; x < data->res_x; x++)
// 		{
// 			uint32_t color = get_pixel(data->ceiling, x, y);
// 			put_pixel(data->win->img, x, y, color);
// 		}
// 	}
// }

void draw_ceiling(t_data *data, int x, int y_end, t_img *ceiling)
{
	int y;
	int tex_x, tex_y;
	uint32_t color;

	if (!ceiling || !ceiling->data)
		return;

	for (y = 0; y < y_end; y++)
	{
		tex_x = x % ceiling->width;    // répétition horizontale si x dépasse
		tex_y = y % ceiling->height;   // répétition verticale si y dépasse
		if (tex_x < 0) tex_x += ceiling->width;
		if (tex_y < 0) tex_y += ceiling->height;
		color = get_pixel(ceiling, tex_x, tex_y);
		put_pixel(data->win->img, x, y, color);
	}
}

#endif