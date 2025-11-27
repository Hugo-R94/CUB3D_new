/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:09:46 by hugz              #+#    #+#             */
/*   Updated: 2025/11/27 13:28:52 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

void	clear_mobs(t_data *data)
{
	if (data->mob)
	{
		free(data->mob);
		data->mob = NULL;
	}
	data->mob_count = 0;
}

void	play_survivor_mode(t_data *data)
{
	if (data->map->map)
		free_map(data->map->map);
	survivor_map(data);
	clear_mobs(data);
	get_player_original_pos(data);
	data->player.is_alive = 1;
	data->current_pg = GAME_PG;
}

void	play_mainmenu(t_data *data)
{
	data->current_pg = HOME_PG;
	data->player_hp = 100;
	data->current_buttons = g_home_button;
}

void	retry_game(t_data *data)
{
	new_map_random(data);
	data->player_hp = 100;
	data->game_on = 1;
	data->current_pg = GAME_PG;
}

#endif