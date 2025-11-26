/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compose_ceilling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:43:49 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/26 11:04:41 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

static inline uint32_t	blend50(uint32_t under, uint32_t over)
{
	uint8_t	r1;
	uint8_t	g1;
	uint8_t	b1;
	uint8_t	r2;
	uint8_t	g2;

	r1 = (under >> 16) & 0xFF;
	g1 = (under >> 8) & 0xFF;
	b1 = under & 0xFF;
	r2 = (over >> 16) & 0xFF;
	g2 = (over >> 8) & 0xFF;
	return (((((r1 + r2) / 2) << 16) | (((g1 + g2) / 2) << 8)
			| ((b1 + ((over & 0xFF))) / 2)));
}

static void	calc_offset(t_data *data, float factor, int offset[2], int *off)
{
	off[0] = ((int)(data->player.parralax_x * 1.81 * 2)
			+ (int)(data->player.px * 5)) * factor + offset[0];
	off[1] = (int)(((data->tilt + data->player.py) * (-factor)))
		- 600 - offset[1];
}

static void	process_pixel(t_img *dest, t_txt *layer, int pos[4])
{
	int			tex_x;
	int			tex_y;
	uint32_t	color;
	uint32_t	base_color;

	tex_x = (pos[0] + pos[2]) % layer->img.width;
	tex_y = (pos[1] + pos[3]) % layer->img.height;
	if (tex_x < 0)
		tex_x += layer->img.width;
	if (tex_y < 0)
		tex_y += layer->img.height;
	color = get_pixel(&layer->img, tex_x, tex_y);
	if (color != 0x000000)
	{
		base_color = get_pixel(dest, pos[0], pos[1]);
		if (base_color != 0x000000)
			color = blend50(base_color, color);
		put_pixel(dest, pos[0], pos[1], color);
	}
}

void	draw_parallax_layer(t_param *params, float factor)
{
	int	x;
	int	y;
	int	off[2];

	calc_offset(params->data, factor, params->offset, off);
	y = -1;
	while (++y < params->dest->height)
	{
		x = -1;
		while (++x < params->dest->width)
			process_pixel(params->dest, params->layer,
				(int []){x, y, off[0], off[1]});
	}
}

void	draw_ceiling_img(t_data *data)
{
	t_txt		*texture;
	t_param		params;

	texture = find_texture(data->txt, "skybox");
	if (texture)
	{
		params = (t_param){data,
			data->ceiling, texture, 1.0f, {0, 0}};
		draw_parallax_layer(&params, 1.0f);
	}
	texture = find_texture(data->txt, "cloud_1");
	if (texture)
	{
		params = (t_param){data, data->ceiling, texture, 1.2f, {2456, 0}};
		draw_parallax_layer(&params, 1.2f);
		params.offset[0] = 323;
		params.offset[1] = 25;
		draw_parallax_layer(&params, 1.35f);
		params.offset[0] = -4342;
		params.offset[1] = 50;
		draw_parallax_layer(&params, 1.6f);
		params.offset[0] = -233;
		params.offset[1] = 75;
		draw_parallax_layer(&params, 1.8f);
	}
}

#endif