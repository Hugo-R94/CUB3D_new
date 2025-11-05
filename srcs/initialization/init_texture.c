/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:40:21 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/28 15:40:30 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	sub_init_game_data(t_data *data, int i, int h, int w)
{
	data->map->textures[i].img.image = mlx_xpm_file_to_image(
			data->win->mlx, data->map->textures[i].path, &w, &h);
	if (!data->map->textures[i].img.image)
	{
		printf("Error: invalid texture: %s\n",
			data->map->textures[i].path);
		clean_exit_mand(data);
	}
	data->map->textures[i].img.width = w;
	data->map->textures[i].img.height = h;
	data->map->textures[i].img.data = mlx_get_data_addr(
			data->map->textures[i].img.image,
			&data->map->textures[i].img.bpp,
			&data->map->textures[i].img.size_line,
			&data->map->textures[i].img.format);
}

void	init_textures_mand(t_data *data)
{
	int	w;
	int	h;
	int	i;

	w = 125;
	h = 125;
	i = -1;
	while (++i < 4)
	{
		data->map->textures[i].path[strcspn(data->map->textures[i].path,
				"\n")] = 0;
	}
	i = -1;
	while (++i < 4)
		sub_init_game_data(data, i, h, w);
}
