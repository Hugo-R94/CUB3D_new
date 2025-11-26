/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_press_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:19:15 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/25 14:18:41 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS

static void	handle_special_keys(int keycode, t_data *data)
{
	if (keycode == 65505)
	{
		data->player.mouv_speed *= 2;
		data->shift_is_press = 1;
	}
	if (keycode == 65507)
		data->player.mouv_speed /= 2;
	if (keycode == 65289)
		data->hud_key_pressed = 1;
	if (keycode == 65362 && data->player_hp < 100)
		data->player_hp += 25;
	if (keycode == 65364 && data->player_hp > 0)
		data->player_hp -= 25;
	if (keycode == 97)
		data->a_is_press = 1;
	if (keycode == 100)
		data->d_is_press = 1;
	if (keycode == 115)
		data->s_is_press = 1;
	if (keycode == 119)
		data->w_is_press = 1;
}

int	handle_key_press(int keycode, t_data *data)
{
	if (keycode == 101)
		action_key(data);
	if (keycode == 111)
		data->o_is_press = 1;
	if (keycode == 112)
		data->p_is_press = 1;
	handle_special_keys(keycode, data);
	return (0);
}

static void	release_special_keys(int keycode, t_data *data)
{
	if (keycode == 65289)
		data->hud_key_pressed = 0;
	if (keycode == 65505)
	{
		data->shift_is_press = 0;
		data->player.mouv_speed /= 2;
	}
	if (keycode == 65507)
		data->player.mouv_speed *= 2;
	if (keycode == 97)
		data->a_is_press = 0;
	if (keycode == 100)
		data->d_is_press = 0;
	if (keycode == 115)
		data->s_is_press = 0;
	if (keycode == 119)
		data->w_is_press = 0;
}

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == 65307)
		handle_escape_key(data);
	if (keycode == 111)
		data->o_is_press = 0;
	if (keycode == 112)
		data->p_is_press = 0;
	release_special_keys(keycode, data);
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