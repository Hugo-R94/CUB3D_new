/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_mand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:14:29 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/28 13:28:22 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifndef BONUS

#include <math.h>

#define MOVE_SPEED 0.02
#define ROT_SPEED 0.006	

static void	update_direction_vector(t_data *data)
{
	data->player.pdx = cos(data->player.pa) * 3;
	data->player.pdy = sin(data->player.pa) * 3;
}

static void	handle_rotation(t_data *data)
{
	// printf("move speed = %f\n",data->player.mouv_speed);
	if (data->a_is_press)
	{
		data->player.pa -= data->player.rot_speed;
		if (data->player.pa < 0)
			data->player.pa += 2 * M_PI;
		update_direction_vector(data);
	}
	if (data->d_is_press)
	{
		data->player.pa += data->player.rot_speed;
		if (data->player.pa > 2 * M_PI)
			data->player.pa -= 2 * M_PI;
		update_direction_vector(data);
	}
}


static void	handle_movement(t_data *data)
{
	double next_px;
	double next_py;

	// Avancer
	if (data->w_is_press)
	{
		next_px = data->player.px + cos(data->player.pa) * data->player.mouv_speed;
		next_py = data->player.py + sin(data->player.pa) * data->player.mouv_speed;

		// Vérifie la map : empêche d'entrer dans un mur
		if (data->map->map[(int)next_py][(int)data->player.px] != '1')
			data->player.py = next_py;
		if (data->map->map[(int)data->player.py][(int)next_px] != '1')
			data->player.px = next_px;
	}

	// Reculer
	if (data->s_is_press)
	{
		next_px = data->player.px - cos(data->player.pa) * data->player.mouv_speed;
		next_py = data->player.py - sin(data->player.pa) * data->player.mouv_speed;

		if (data->map->map[(int)(next_py)][(int)(data->player.px)] != '1')
			data->player.py = next_py;
		if (data->map->map[(int)(data->player.py)][(int)(next_px)] != '1')
			data->player.px = next_px;
	}
	// printf("px=%.2f py=%.2f next_px=%.2f next_py=%.2f\n", 
	// data->player.px, data->player.py, next_px, next_py);

}


void	mouv_player(t_data *data)
{
	if (!data)
		return ;
	handle_rotation(data);
	handle_movement(data);
}

int	handle_key_press(int keycode, t_data *data)
{
	(void)data;
	// printf("%skey pressed = %i\n%s",GRN, keycode, RESET);
	if (keycode == 97)
	{
		// printf("gauche\n");
		// data->player.px -= 0.1;
		data->a_is_press = 1;
	}
	if (keycode == 100)
	{
		// printf("droite\n");
		// data->player.px += 0.1;
		// data->player.pa += 0.1;
		// if(data->player.pa > 2 * M_PI)
		// 	data->player.pa -= 2 * M_PI;
		// data->player.pdx = cos(data->player.pa) * 5;
		// data->player.pdy = sin(data->player.pa) * 5;
		data->d_is_press = 1;
	}
	if (keycode == 115)
	{
		// printf("bas\n");
		// data->player.py += 0.1;
		data->s_is_press = 1;
	}
	if (keycode == 119)
	{
		// printf("haut\n");
		// data->player.py -= 0.1;
		data->w_is_press = 1;
	}
	return (0);
}

int	handle_key_release(int keycode, t_data *data)
{
	// printf("%skey released = %i%s\n",RED, keycode, RESET);
	if (keycode == 65307)
		clean_exit_mand(data);
	if (keycode == 97)
	{
		// printf("gauche\n");
		// data->player.px -= 0.1;
		data->a_is_press = 0;
	}
	if (keycode == 100)
	{
		// printf("droite\n");
		// data->player.px += 0.1;
		// data->player.pa += 0.1;
		// if(data->player.pa > 2 * M_PI)
		// 	data->player.pa -= 2 * M_PI;
		// data->player.pdx = cos(data->player.pa) * 5;
		// data->player.pdy = sin(data->player.pa) * 5;
		data->d_is_press = 0;
	}
	if (keycode == 115)
	{
		// printf("bas\n");
		// data->player.py += 0.1;
		data->s_is_press = 0;
	}
	if (keycode == 119)
	{
		// printf("haut\n");
		// data->player.py -= 0.1;
		data->w_is_press = 0;
	}
	return (0);
}
#endif	