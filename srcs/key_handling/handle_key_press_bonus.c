/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_press_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:19:15 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/30 12:49:02 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#ifdef BONUS


#define MOVE_SPEED 0.05
#define ROT_SPEED 0.03

// static void	update_direction_vector(t_data *data)
// {
// 	data->player.pdx = cos(data->player.pa) * 3;
// 	data->player.pdy = sin(data->player.pa) * 3;
// }

static void	handle_rotation(t_data *data)
{
	// if (data->a_is_press)
	// {
	// 	data->player.pa -= data->player.rot_speed;
	// 	if (data->player.pa < 0)
	// 		data->player.pa += 2 * M_PI;
	// 	update_direction_vector(data);
	// }
	// if (data->d_is_press)
	// {
	// 	data->player.pa += data->player.rot_speed;
	// 	if (data->player.pa > 2 * M_PI)
	// 		data->player.pa -= 2 * M_PI;
	// 	update_direction_vector(data);
	// }
	// printf("pa = %f | x accel = %d | diff = %f\n",data->player.pa, data->mouse.x_accel, data->player.pa - data->mouse.x_accel);
	// float sensitivity = 0.01f; // à ajuster selon le feeling
	// data->player.pa += data->mouse.x_accel * sensitivity;
	// // normaliser l'angle pour qu'il reste dans [0, 2PI]
	// if (data->player.pa < 0)
	// 	data->player.pa += 2 * M_PI;
	// else if (data->player.pa >= 2 * M_PI)
	// 	data->player.pa -= 2 * M_PI;
	if (data)
		printf("");

}


static void	handle_movement(t_data *data)
{
	double next_px;
	double next_py;
	double move_speed = data->player.mouv_speed;

	// Avancer
	if (data->w_is_press)
	{
		next_px = data->player.px + cos(data->player.pa) * move_speed;
		next_py = data->player.py + sin(data->player.pa) * move_speed;

		if (data->map->map[(int)next_py][(int)data->player.px] != '1')
			data->player.py = next_py;
		if (data->map->map[(int)data->player.py][(int)next_px] != '1')
			data->player.px = next_px;
	}

	// Reculer
	if (data->s_is_press)
	{
		next_px = data->player.px - cos(data->player.pa) * move_speed;
		next_py = data->player.py - sin(data->player.pa) * move_speed;

		if (data->map->map[(int)(next_py)][(int)data->player.px] != '1')
			data->player.py = next_py;
		if (data->map->map[(int)data->player.py][(int)(next_px)] != '1')
			data->player.px = next_px;
	}

	// Strafe à gauche (A)
	if (data->d_is_press)
	{
		next_px = data->player.px - sin(data->player.pa) * move_speed;
		next_py = data->player.py + cos(data->player.pa) * move_speed;

		if (data->map->map[(int)next_py][(int)data->player.px] != '1')
			data->player.py = next_py;
		if (data->map->map[(int)data->player.py][(int)next_px] != '1')
			data->player.px = next_px;
	}

	// Strafe à droite (D)
	if (data->a_is_press)
	{
		next_px = data->player.px + sin(data->player.pa) * move_speed;
		next_py = data->player.py - cos(data->player.pa) * move_speed;

		if (data->map->map[(int)next_py][(int)data->player.px] != '1')
			data->player.py = next_py;
		if (data->map->map[(int)data->player.py][(int)next_px] != '1')
			data->player.px = next_px;
	}
}



void	mouv_player(t_data *data)
{
	if (!data)
		return ;
	if(data->current_pg == GAME_PG)
	{
		handle_rotation(data);
		handle_movement(data);
	}
}

int	handle_key_press(int keycode, t_data *data)
{
	// printf("keycode = %d",keycode);
	if (keycode ==  65505) // shift
	{
		data->player.mouv_speed *= 2;
		data->shift_is_press = 1;
	}
	if (keycode == 65507)
		data->player.mouv_speed /= 2;
	if (keycode == 111)
	{
		data->o_is_press = 1;
	}
	if (keycode == 112)
	{
		data->p_is_press = 1;
	}
	if (keycode == 65289)
		data->hud_key_pressed = 1;
	if (keycode == 65362)
	{
		if(data->player_hp<100)
			data->player_hp += 25;
	}
	if (keycode == 65364)
	{
		if(data->player_hp > 0)
			data->player_hp -= 25;
	}
	if (keycode == 97)
	{
		// data->player.px -= 0.1;
		data->a_is_press = 1;
	}
	if (keycode == 100)
	{
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
		// data->player.py += 0.1;
		data->s_is_press = 1;
	}
	if (keycode == 119)
	{
		// data->player.py -= 0.1;
		data->w_is_press = 1;
	}
	return (0);
}

void	handle_escape_key(t_data *data)
{
	if (data->current_pg == GAME_PG)
		data->current_pg = PAUSE_PG;
	else if (data->current_pg == PAUSE_PG)
		data->current_pg = GAME_PG;
	else if (data->current_pg == GMP_PG || data->current_pg == SETT_PG)
	{
		data->current_pg = HOME_PG;
		data->current_buttons = g_home_button;
	}
	else
		clean_and_exit(data, 0);
}

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == 65289)
		data->hud_key_pressed = 0;
	if (keycode == 65307)
		handle_escape_key(data);
	if (keycode ==  65505)
	{
		data->shift_is_press = 0;
		data->player.mouv_speed /= 2;
	}
	if (keycode == 65507)
		data->player.mouv_speed *= 2;
	if (keycode == 97)
	{
		data->a_is_press = 0;
	}
	if (keycode == 111)
	{
		data->o_is_press = 0;
	}
	if (keycode == 112)
	{
		data->p_is_press = 0;
	}
	if (keycode == 100)
	{
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
		// data->player.py += 0.1;
		data->s_is_press = 0;
	}
	if (keycode == 119)
	{
		// data->player.py -= 0.1;
		data->w_is_press = 0;
	}
	return (0);
}

void	handle_key_game(t_data *data)
{
	if (data->hud_key_pressed)
	{
		if (data->pos_y_hud > 0 && data->game_on == 1)
			data->pos_y_hud -= 75;
	}
	else
	{
		if (data->pos_y_hud < 300 && data->game_on == 1)
			data->pos_y_hud += 75;
	}
}
#endif