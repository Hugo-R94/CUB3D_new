/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:45:58 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/19 18:43:03 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_player_original_or(t_data *data, char player)
{
    if (player == 'N')   // Nord = vers le haut
        data->player.pa = 3 * M_PI / 2;
    else if (player == 'S') // Sud = vers le bas
        data->player.pa = M_PI / 2;
    else if (player == 'E') // Est = vers la droite
        data->player.pa = 0;
    else if (player == 'O') // Ouest = vers la gauche
        data->player.pa = M_PI;

    // Calcul du vecteur de direction à partir de l'angle
    data->player.pdx = cos(data->player.pa);
    data->player.pdy = sin(data->player.pa);
}


void get_player_original_pos(t_data  *data)
{
	int	x;
	int	y;
	
	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] == 'S' || data->map->map[y][x] == 'N'
				|| data->map->map[y][x] == 'O' || data->map->map[y][x] == 'E')
				{
					data->player.px = x + 0.5;
					data->player.py = y + 0.5;
					get_player_original_or(data, data->map->map[y][x]);	
				}
				x++;
		}
		y++;
	}
}