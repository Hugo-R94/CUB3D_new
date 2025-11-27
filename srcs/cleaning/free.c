/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:38:38 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/27 13:23:34 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	clean_windows(t_win *win)
{
	if (!win)
		return ;
	if (win->mlx && win->img)
		mlx_destroy_image(win->mlx, win->img);
	if (win->mlx && win->win)
		mlx_destroy_window(win->mlx, win->win);
	if (win->mlx)
		mlx_destroy_display(win->mlx);
	free(win->mlx);
	free(win);
}

#ifdef BONUS

void	clean_data(t_data *data)
{
	if (!data)
		return ;
	if (data->txt)
		free_textures(data->txt);
	if (data->map)
	{
		if (data->map->map)
			free_map(data->map->map);
		free(data->map);
	}
	if (data->raycast_f)
		free(data->raycast_f);
	free(data);
}

void	free_textures(t_txt *textures)
{
	int	i;

	i = 0;
	while (textures[i].name)
	{
		free(textures[i].name);
		free(textures[i].path);
		i++;
	}
	free(textures);
}

#endif