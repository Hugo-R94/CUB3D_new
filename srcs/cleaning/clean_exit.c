/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:24:36 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/10 12:57:45 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#ifdef BONUS

int	clean_and_exit(t_data *data, int exit_code)
{
	if (data)
	{
		if (data->ceiling)
		{
			if (data->ceiling->image)
				mlx_destroy_image(data->win->mlx, data->ceiling);
			if(data->ceiling)
				free(data->ceiling);
		}
		clean_windows(data->win);
		clean_data(data);
	}
	exit(exit_code);
}

void destroy_all_img(t_data *data)
{
	int i;
	
	i = 0;
	if (data->ceiling)
	{
		mlx_destroy_image(data->win->mlx, data->ceiling);
		data->ceiling = NULL;
	}
	while (data->txt[i].name)
	{
		if (data->txt[i].img.image)
			mlx_destroy_image(data->win->mlx, data->txt[i].img.image);
		i++;
	}
	
}

void	clear_and_exit(t_data *data)
{
	if (data)
	{
		destroy_all_img(data);
		clean_windows(data->win);
		clean_data(data);
	}
	exit(0);
}
#endif