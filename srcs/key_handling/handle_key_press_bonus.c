/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_press_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:19:15 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/24 15:28:34 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


// static void	update_direction_vector(t_data *data)
// {
// 	data->player.pdx = cos(data->player.pa) * 3;
// 	data->player.pdy = sin(data->player.pa) * 3;
// }

// int		is_wall(t_data *data, int x, int y)
// {
// 	if (x < 0 || y < 0 || x >= data->map->width || y >= data->map->height)
//         return (-1);
// 	if (data->map->map[x][y] == '1' || data->map->map[x][y] == '2'
// 		|| data->map->map[x][y] == '3' || data->map->map[x][y] == 'D')
// 		return(1);
// 	return(0);
// }
#ifdef BONUS




static void	handle_movement(t_data *data)
{
	double next_px;
	double next_py;
	double move_speed = data->player.mouv_speed;
	static int pole = -1;
	// Avancer
	static int up = 1;

	if (data->w_is_press || data->d_is_press || data->s_is_press || data->a_is_press)
	{
		if (up == 1)
			if (data->player.pl_height <= 7)
				data->player.pl_height += (2 * data->player.mouv_speed * 10);
			else
				up = 0;
		else
			if (data->player.pl_height >= -7)
				data->player.pl_height -= (2 * data->player.mouv_speed * 10 );
			else
				up = 1;		
			
	}//change collision system like for this one 
	if (data->w_is_press)
	{
		next_px = data->player.px + cos(data->player.pa) * move_speed;
		next_py = data->player.py + sin(data->player.pa) * move_speed;

		if (!check_wall_collision(data, data->player.px, next_py, 0.1))
			data->player.py = next_py;
		if (!check_wall_collision(data, next_px, data->player.py, 0.1))
			data->player.px = next_px;
	}

	// Reculer
	if (data->s_is_press)
	{
		next_px = data->player.px - cos(data->player.pa) * move_speed;
		next_py = data->player.py - sin(data->player.pa) * move_speed;

		
		if (!check_wall_collision(data, data->player.px, next_py, 0.1))
			data->player.py = next_py;
		if (!check_wall_collision(data, next_px, data->player.py, 0.1))
			data->player.px = next_px;
	}

	// Strafe à gauche (A)
	if (data->d_is_press)
	{
		next_px = data->player.px - sin(data->player.pa) * move_speed;
		next_py = data->player.py + cos(data->player.pa) * move_speed;

		
		if (!check_wall_collision(data, data->player.px, next_py, 0.1))
			data->player.py = next_py;
		if (!check_wall_collision(data, next_px, data->player.py, 0.1))
			data->player.px = next_px;
	}

	// Strafe à droite (D)
	if (data->a_is_press)
	{
		next_px = data->player.px + sin(data->player.pa) * move_speed;
		next_py = data->player.py - cos(data->player.pa) * move_speed;

		
		if (!check_wall_collision(data, data->player.px, next_py, 0.1))
			data->player.py = next_py;
		if (!check_wall_collision(data, next_px, data->player.py, 0.1))
			data->player.px = next_px;
	}
}



void	mouv_player(t_data *data)
{
	if (!data)
		return ;
	if(data->current_pg == GAME_PG)
		handle_movement(data);
}


void action_key(t_data *data)
{
    int next_x;
    int next_y;
    
    if (!data || !data->map || !data->map->map)
        return;
    
    next_x = data->player.px;
    next_y = data->player.py;
    
    double angle = fmod(data->player.pa, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    
    if (angle >= 7 * M_PI / 4 || angle < M_PI / 4)
        next_x++;
    else if (angle >= M_PI / 4 && angle < 3 * M_PI / 4)
        next_y++;
    else if (angle >= 3 * M_PI / 4 && angle < 5 * M_PI / 4)
        next_x--;
    else
        next_y--;
    
    if (next_y >= 0 && data->map->map[next_y] && 
        next_x >= 0 && data->map->map[next_y][next_x])
    {
        if (data->map->map[next_y][next_x] == 'D' || 
            data->map->map[next_y][next_x] == 'L')
        {
            data->door_state = 1;
            // Changer l'état de la porte
            if (data->map->map[next_y][next_x] == 'D')
                data->map->map[next_y][next_x] = 'L';
            else
			{
				data->door_state = 0;
                data->map->map[next_y][next_x] = 'D';
			}
        }
    }
}


int	handle_key_press(int keycode, t_data *data)
{
	if (keycode == 101)
		action_key(data);
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
		clear_and_exit(data);
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