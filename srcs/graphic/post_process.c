/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:58:14 by hugz              #+#    #+#             */
/*   Updated: 2025/11/26 13:38:28 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

uint32_t	pp_px_depth(uint32_t color, float depth)
{
	float		factor;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	float		dark;

	if (depth <= 0)
		return (color);
	factor = depth * depth / 100.0f;
	if (factor > 1.0f)
		factor = 1.0f;
	if (factor < 0.0f)
		factor = 0.0f;
	dark = 1.0f - factor;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (uint8_t)(r * dark);
	g = (uint8_t)(g * dark);
	b = (uint8_t)(b * dark);
	return ((r << 16) | (g << 8) | b);
}

static void	apply_depth_effect_pixel(t_f_img *f_img, int i, float center_y)
{
	int		y;
	float	offset_y;
	float	adjusted_depth;
	t_px	*px;

	px = &f_img->pixels[i];
	if (px->depth < 0)
		return ;
	if (px->type == PX_MOB && px->color != 0xFF0000)
	{
		y = i / f_img->width;
		offset_y = (y - center_y) * 0.03f;
		adjusted_depth = sqrtf(px->depth * px->depth
				+ offset_y * offset_y);
		px->color = pp_px_depth(px->color, adjusted_depth);
	}
	else
		px->color = pp_px_depth(px->color, px->depth);
	if (px->color == 0x000000)
		px->color = 0x000001;
}

void	pp_depth(t_f_img *f_img)
{
	float	center_y;
	int		i;

	if (!f_img)
		return ;
	center_y = f_img->height / 2.0f;
	i = 0;
	while (i < f_img->height * f_img->width)
	{
		apply_depth_effect_pixel(f_img, i, center_y);
		i++;
	}
}

void	render_px_type(t_f_img *f_img)
{
	int	i;

	i = 0;
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
	int	i;

	i = 0;
	while (i < f_img->height * f_img->width)
	{
		if (f_img->pixels[i].type == PX_MOB)
			f_img->pixels[i].color = 0xFF0000;
		i++;
	}
}

#endif