/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture_mand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:51:16 by hugz              #+#    #+#             */
/*   Updated: 2025/11/27 11:51:23 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifndef BONUS

static t_txt	*get_horizontal_texture(t_data *data, float ra)
{
	if (sin(ra) > 0)
		return (&data->map->textures[1]);
	else
		return (&data->map->textures[0]);
}

static t_txt	*get_vertical_texture(t_data *data, float ra)
{
	if (cos(ra) > 0)
		return (&data->map->textures[2]);
	else
		return (&data->map->textures[3]);
}

t_txt	*find_wall_txt(t_data *data, float dist_h, float dist_v, float ra)
{
	if (dist_h < dist_v)
		return (get_horizontal_texture(data, ra));
	else
		return (get_vertical_texture(data, ra));
}

int	get_texture_x(t_img *img, float wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * img->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= img->width)
		tex_x = img->width - 1;
	return (tex_x);
}

#endif