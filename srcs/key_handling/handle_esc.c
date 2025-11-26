/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_esc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:18:43 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 14:19:04 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS 

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

#endif