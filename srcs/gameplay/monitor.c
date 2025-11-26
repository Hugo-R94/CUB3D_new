/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:29:59 by hugz              #+#    #+#             */
/*   Updated: 2025/11/26 14:30:18 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

void	monitor_player(t_data *data)
{
	if (data->player_hp <= 0)
	{
		data->current_buttons = g_death_menu;
		data->current_pg = DEATH_PG;
	}
	if (check_collision(data, (float []){data->player.px, data->player.py},
		0.1f, 'X'))
		data->current_pg = WIN_PG;
}

#endif