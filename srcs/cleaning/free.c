/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:38:38 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/04 13:28:52 by hrouchy          ###   ########.fr       */
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

void	free_ledata(t_map *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (i < 4)
	{
		free(data->textures[i].path);
		i++;
	}
	free_tab(data->map);
	free(data);
}

#ifdef BONUS

void	clean_data(t_data *data)
{
	if (!data)
		return ;
	if (data->txt)
		free_textures(data, data->txt);
	if (data->map)
	{
		if (data->map->map)
			free_map(data->map->map);
		free(data->map);
	}
	free(data->ceiling);
	free(data);
}

void	free_textures(t_data *data, t_txt *textures)
{
	int	i;

	i = 0;
	if (data)
		printf("");
	while (textures[i].name)
	{
		// if (data->win->mlx && textures[i].img.image)
		// 	mlx_destroy_image(data->win->mlx, textures[i].img.image);
		free(textures[i].name);
		free(textures[i].path);
		i++;
	}
	free(textures);
}

#endif