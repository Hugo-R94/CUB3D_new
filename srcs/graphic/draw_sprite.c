/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:30:36 by hugz              #+#    #+#             */
/*   Updated: 2025/11/26 12:11:04 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS 

static void	draw_sprite_pixel(t_data *data, int x, int y, int depth_color[2])
{
	int	index;

	index = y * data->render_gmp->width + x;
	if (index < 0
		|| index >= data->render_gmp->width * data->render_gmp->height)
		return ;
	if (data->render_gmp->pixels[index].type == PX_EMPTY
		|| (float)depth_color[1] / 1000.0f
		< data->render_gmp->pixels[index].depth)
	{
		data->render_gmp->pixels[index].color = depth_color[0];
		data->render_gmp->pixels[index].type = PX_MOB;
		data->render_gmp->pixels[index].depth = (float)depth_color[1]
			/ 1000.0f;
	}
}

static void	draw_sprite_column(t_data *data, t_txt *tex, int x, int bounds[7])
{
	int		y;
	int		tex_xy[2];
	int		color;
	float	ratios[2];
	int		depth_color[2];

	compute_ratios(ratios, tex, bounds);
	tex_xy[0] = get_tex_coord(x, bounds[2], ratios[0], tex->img.width);
	y = bounds[4] - 1;
	while (++y < bounds[5])
	{
		if (y < 0 || y >= data->render_gmp->height)
			continue ;
		tex_xy[1] = get_tex_coord(y, bounds[4], ratios[1], tex->img.height);
		color = get_pixel(&tex->img, tex_xy[0], tex_xy[1]);
		if (color != 0x000000)
		{
			depth_color[0] = color;
			depth_color[1] = bounds[6];
			draw_sprite_pixel(data, x, y, depth_color);
		}
	}
}

static void	render_sprite_columns(t_data *data, t_txt *tex, int bounds[7])
{
	int	x;

	x = bounds[2] - 1;
	while (++x < bounds[3])
	{
		if (x >= 0 && x < data->render_gmp->width)
			draw_sprite_column(data, tex, x, bounds);
	}
}

static void	calc_sprite_bounds(t_data *data, float params[3], int bounds[7])
{
	int	full_height;
	int	center_y;

	bounds[1] = (int)(data->render_gmp->height / params[2] * params[1]);
	bounds[0] = (int)(data->render_gmp->height / params[2] * params[1]);
	full_height = (int)(data->render_gmp->height / params[2]);
	center_y = (data->render_gmp->height / 2) + data->tilt
		+ data->player.pl_height;
	bounds[5] = center_y + (full_height / 2);
	bounds[4] = bounds[5] - bounds[0];
	bounds[2] = get_screen_x(params[0], data->fov) - bounds[1] / 2;
	bounds[3] = bounds[2] + bounds[1];
	bounds[6] = (int)(params[2] * 1000);
}

void	draw_sprite(t_data *data, float pos[2], char *sprite_name, float size)
{
	float	distance;
	float	relative_angle;
	int		bounds[7];
	t_txt	*tex;
	float	params[3];

	distance = calc_distance(data, pos[0], pos[1]);
	if (distance < 0.1f)
		return ;
	if (distance > 25.5)
		return ;
	relative_angle = get_angle_to_sprite(data, pos[0], pos[1]);
	if (fabs(relative_angle) > data->fov / 2)
		return ;
	tex = find_texture(data->txt, sprite_name);
	if (!tex)
		return ;
	params[0] = relative_angle;
	params[1] = size;
	params[2] = distance;
	calc_sprite_bounds(data, params, bounds);
	render_sprite_columns(data, tex, bounds);
}

#endif