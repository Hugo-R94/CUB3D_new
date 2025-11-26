/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceilling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:04:18 by hugz              #+#    #+#             */
/*   Updated: 2025/11/26 11:04:44 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

void	draw_ceiling_pixel(t_data *data, t_img *ceiling, int x, int y)
{
	int			tex_x;
	int			tex_y;
	uint32_t	color;
	int			index;

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
		data->render_gmp->pixels[index].color = color;
		data->render_gmp->pixels[index].depth = -1;
		data->render_gmp->pixels[index].type = PX_EMPTY;
	}
}

void	draw_ceiling(t_data *data, int x, int y_end, t_img *ceiling)
{
	int	y;

	if (!ceiling || !ceiling->data)
		return ;
	if (x < 0 || x >= data->render_gmp->width)
		return ;
	y = -1;
	while (++y < y_end && y < data->render_gmp->height)
		draw_ceiling_pixel(data, ceiling, x, y);
}

#endif