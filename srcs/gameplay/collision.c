/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:08:59 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 11:40:15 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS 

static void	apply_mob_knockback(t_data *data, int j, float dist, float force)
{
	float	mv[2];
	float	next[2];

	if (dist < 0.01f)
		dist = 0.01f;
	mv[0] = (data->mob[j].mx - data->player.px) / dist * force / 10.0f;
	mv[1] = (data->mob[j].my - data->player.py) / dist * force / 10.0f;
	if (data->mob[j].knockback_timer < 10)
	{
		next[0] = data->mob[j].mx + mv[0];
		if (!check_wall_collision(data, next[0], data->mob[j].my, 0.1))
			data->mob[j].mx = next[0];
		next[1] = data->mob[j].my + mv[1];
		if (!check_wall_collision(data, data->mob[j].mx, next[1], 0.1))
			data->mob[j].my = next[1];
		data->mob[j].knockback_timer++;
	}
	else
	{
		data->mob[j].knockback = 0;
		data->mob[j].knockback_timer = 0;
	}
}

void	knockback(t_data *data)
{
	float	dist;
	float	force;
	int		j;

	force = 2.0f;
	j = 0;
	while (j < data->mob_count)
	{
		if (data->mob[j].knockback && data->mob[j].is_alive)
		{
			dist = sqrtf((data->mob[j].mx - data->player.px)
					* (data->mob[j].mx - data->player.px)
					+ (data->mob[j].my - data->player.py)
					* (data->mob[j].my - data->player.py));
			apply_mob_knockback(data, j, dist, force);
		}
		j++;
	}
}

static void	apply_player_knockback(t_data *data, float dist, float force)
{
	float	mv[2];
	float	next[2];

	if (dist < 0.01f)
		dist = 0.01f;
	mv[0] = ((data->player.px - data->mob[0].mx) / dist) * force;
	mv[1] = ((data->player.py - data->mob[0].my) / dist) * force;
	next[0] = data->player.px + mv[0];
	next[1] = data->player.py + mv[1];
	data->player_hp -= 10;
	if (!check_wall_collision(data, next[0], data->player.py, 0.1))
		data->player.px = next[0];
	if (!check_wall_collision(data, data->player.px, next[1], 0.1))
		data->player.py = next[1];
}

void	is_player_hit(t_data *data)
{
	int		j;
	float	dist;
	float	force;

	j = 0;
	force = 0.15f;
	while (j < data->mob_count)
	{
		if (!data->mob[j].is_alive)
		{
			j++;
			continue ;
		}
		dist = sqrtf((data->player.px - data->mob[j].mx)
				* (data->player.px - data->mob[j].mx)
				+ (data->player.py - data->mob[j].my)
				* (data->player.py - data->mob[j].my));
		if (dist < 0.15f && data->mob[j].knockback == 0)
		{
			data->mob[j].knockback = 1;
			apply_player_knockback(data, dist, force);
		}
		j++;
	}
}

#endif