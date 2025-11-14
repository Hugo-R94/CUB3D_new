/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_bonus2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:51:48 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/14 16:01:05 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS
/*
** Assombrit une couleur selon un facteur (0.0 = pas d'effet, 1.0 = noir)
*/
uint32_t darken_color(uint32_t color, float factor)
{
	uint8_t r, g, b;

	if (factor < 0.0f)
		factor = 0.0f;
	if (factor > 1.0f)
		factor = 1.0f;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;

	r = (uint8_t)(r * (1.0f - factor));
	g = (uint8_t)(g * (1.0f - factor));
	b = (uint8_t)(b * (1.0f - factor));

	return ((r << 16) | (g << 8) | b);
}


uint32_t	depth_render(uint32_t color, int ray_length)
{
	if ((int)ray_length <=4 )
		return(darken_color(color, (0.05 * (float)((ray_length)))));
	else if (ray_length <= 12)
		return(darken_color(color, (0.05 * (float)((ray_length * ray_length) / 4))));
	else if (ray_length <=20)
		return(darken_color(color, (0.05 * (float)((ray_length * ray_length) / 3))));
	else
		return(0x100000);
}


#endif