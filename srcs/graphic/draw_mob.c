/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mob.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:44:02 by hugz              #+#    #+#             */
/*   Updated: 2025/11/27 13:46:37 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

static void	draw_mob_pixels(t_data *data, t_txt *tex,
		int *bounds, float *ratios)
{
	int		y;
	int		tex_y;
	int		color;
	int		index;

	y = bounds[4] - 1;
	while (++y < bounds[5])
	{
		if (y < 0 || y >= data->render_gmp->height)
			continue ;
		tex_y = get_tex_coord(y, bounds[4], ratios[1], tex->img.height);
		color = get_pixel(&tex->img, (int)ratios[2], tex_y);
		if (color != 0x000000)
		{
			index = y * data->render_gmp->width + (int)ratios[3];
			if (index >= 0 && index < data->render_gmp->width
				* data->render_gmp->height)
			{
				if (data->render_gmp->pixels[index].type == PX_EMPTY
					|| ratios[4] < data->render_gmp->pixels[index].depth)
					draw_px_info(data, index, color, ratios);
			}
		}
	}
}

static void	draw_mob_sprite(t_data *data, t_txt *tex, int *bounds,
	float depth_id[2])
{
	int		x;
	float	ratios[6];

	x = bounds[2] - 1;
	ratios[4] = depth_id[0];
	ratios[5] = (float)depth_id[1];
	while (++x < bounds[3])
	{
		if (x < 0 || x >= data->render_gmp->width)
			continue ;
		get_mob_ratios(tex, bounds, ratios, x);
		ratios[3] = (float)x;
		draw_mob_pixels(data, tex, bounds, ratios);
	}
}

void	draw_single_mob(t_data *data, int i, char *txt_name, float height_scale)
{
	float	distance;
	float	relative_angle;
	int		bounds[6];
	t_txt	*mob_tex;
	int		center_y;

	distance = calculate_mob_distance(data, i);
	if (distance < 0.1f)
		return ;
	relative_angle = get_relative_angle(data, i);
	if (fabs(relative_angle) > data->fov / 2)
		return ;
	bounds[1] = (int)(data->render_gmp->height / distance * height_scale);
	bounds[0] = (int)(data->render_gmp->height / distance * height_scale);
	center_y = (data->render_gmp->height / 2)
		+ data->tilt + data->player.pl_height;
	bounds[5] = center_y + ((int)(data->render_gmp->height / distance) / 2);
	bounds[4] = bounds[5] - bounds[0];
	bounds[2] = get_screen_x(relative_angle, data->fov) - bounds[1] / 2;
	bounds[3] = bounds[2] + bounds[1];
	mob_tex = find_texture(data->txt, txt_name);
	if (!mob_tex)
		return ;
	draw_mob_sprite(data, mob_tex, bounds, (float []){distance, i});
}

void	check_mob_state(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->mob_count)
	{
		if (data->mob[i].hp <= 0)
			data->mob[i].is_alive = 0;
	}
}

void	draw_mobs(t_data *data)
{
	int	i;

	i = 0;
	check_mob_state(data);
	while (i < data->mob_count && data->mob[i].mx != 0)
	{
		if (data->mob[i].is_alive)
			draw_single_mob(data, i, data->mob[i].sprite, data->mob[i].size);
		i++;
	}
}
#endif