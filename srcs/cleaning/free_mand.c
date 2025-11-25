/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:35:05 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/24 16:34:49 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_textures_mand(t_txt *textures)
{
	int	i;

	if (!textures)
		return ;
	i = 0;
	while (i < 4)
	{
		if (textures[i].path)
		{
			free(textures[i].path);
			textures[i].path = NULL;
		}
		i++;
	}
}

void	free_map_struct(t_data *data, t_map *map)
{
	if (!map)
		return ;
	free_map_content(data, map);
	free(map);
}

void	free_map_content(t_data *data, t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->map)
	{
		i = 0;
		while (map->map[i])
		{
			free(map->map[i]);
			map->map[i] = NULL;
			i++;
		}
		free(map->map);
		map->map = NULL;
	}
	i = -1;
	while (++i < 4)
	{
		if (map->textures[i].img.image)
			mlx_destroy_image(data->win->mlx, map->textures[i].img.image);
	}
	free_textures_mand(map->textures);
}

#ifdef BONUS

void	clean_exit_mand(t_data *data)
{
	if (!data)
		return ;
	if (data->map)
	{
		free_map_struct(data, data->map);
		data->map = NULL;
	}
	if (data->win)
		clean_windows(data->win);
	if (data->raycast_f)
		free(data->raycast_f);
	free(data);
	exit(0);
}

#else 

void	clean_exit_mand(t_data *data)
{
	if (!data)
		return ;
	if (data->map)
	{
		free_map_struct(data, data->map);
		data->map = NULL;
	}
	if (data->win)
		clean_windows(data->win);
	free(data);
	exit(0);
}

#endif