/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:58:14 by hugz              #+#    #+#             */
/*   Updated: 2025/11/24 16:00:12 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

uint32_t darken_color2(uint32_t color, float depth)
{
	uint8_t r, g, b;
	float   factor;
	
	if (depth < 0.0f)
		depth = 0.0f;
	if (depth > 1.0f)
		depth = 1.0f;
	
	factor = 1.0f - depth;
	
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	
	r = (uint8_t)(r * factor);
	g = (uint8_t)(g * factor);
	b = (uint8_t)(b * factor);
	
	return ((r << 16) | (g << 8) | b);
}

float pp_px_depth(uint32_t color, float depth)
{
    float factor;
    
    if (depth <= 0)
        return color;
    
    factor = depth * depth / 100.0f;
    if (factor > 1.0f)
        factor = 1.0f;
    
    return (darken_color2(color, factor));
}

void pp_depth(t_f_img *f_img)
{
	int i;
	int x;
	int y;
	float center_y;
	float offset_y;
	float adjusted_depth;
	float vertical_scale;
	
	center_y = f_img->height / 2.0f;
	vertical_scale = 0.03f;
	i = 0;
	while (i < f_img->height * f_img->width)
	{
		if (f_img->pixels[i].depth >= 0)
		{
			if (f_img->pixels[i].type == PX_MOB && f_img->pixels[i].color != 0xFF0000)
			{
				y = i / f_img->width;
				offset_y = (y - center_y) * vertical_scale;
				adjusted_depth = sqrtf(f_img->pixels[i].depth * f_img->pixels[i].depth 
									  + offset_y * offset_y);
				f_img->pixels[i].color = pp_px_depth(f_img->pixels[i].color, 
													  adjusted_depth);
			}
			else 
		 		f_img->pixels[i].color = pp_px_depth(f_img->pixels[i].color, 
												   f_img->pixels[i].depth);	
		}
		if (f_img->pixels[i].color == 0x000000)
			f_img->pixels[i].color = 0x000001;
		i++;
	}
}

void	render_px_type(t_f_img *f_img)
{
	int i;

	i = 0;
	// printf("renderpxtype\n");
	while (i < f_img->height * f_img->width)
	{
		if (f_img->pixels[i].type == PX_MOB)
			f_img->pixels[i].color = 0xFF0000;
		else if (f_img->pixels[i].type == PX_WALL)
			f_img->pixels[i].color = 0x00FF00;
		else
			f_img->pixels[i].color = 0x0000FF;
		i++;
	}
}

void	render_px_type_mob(t_f_img *f_img)
{
	int i;

	i = 0;
	// printf("renderpxtype\n");
	while (i < f_img->height * f_img->width)
	{
		if (f_img->pixels[i].type == PX_MOB)
			f_img->pixels[i].color = 0xFF0000;
		i++;
	}
}