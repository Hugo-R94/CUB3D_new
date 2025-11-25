/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:59:07 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 12:28:17 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

// int check_wall_collision(t_data *data, float x, float y, float r)
// {
// 	// Check les 4 coins de la hitbox
// 	if (data->map->map[(int)(y - r)][(int)(x - r)] == '1')
// 		return (1);
// 	if (data->map->map[(int)(y - r)][(int)(x + r)] == '1')
// 		return (1);
// 	if (data->map->map[(int)(y + r)][(int)(x - r)] == '1')
// 		return (1);
// 	if (data->map->map[(int)(y + r)][(int)(x + r)] == '1')
// 		return (1);
// 	return (0);
// }

void	move_mob_toward(t_data *data, int i)
{
	float	d[2];
	float	dist;
	float	speed;
	float	next[2];
	float	r;

	r = 0.13f;
	speed = 0.05f;
	d[0] = data->player.px - data->mob[i].mx;
	d[1] = data->player.py - data->mob[i].my;
	dist = sqrtf(d[0] * d[0] + d[1] * d[1]);
	if (dist < 0.001f)
		return ;
	d[0] /= dist;
	d[1] /= dist;
	next[0] = data->mob[i].mx + d[0] * speed;
	next[1] = data->mob[i].my + d[1] * speed;
	if (!check_wall_collision(data, next[0], data->mob[i].my, r))
		data->mob[i].mx = next[0];
	if (!check_wall_collision(data, data->mob[i].mx, next[1], r))
		data->mob[i].my = next[1];
}

static void	apply_repulsion(t_data *data, int i, int j)
{
	float	d[2];
	float	dist;
	float	push;
	float	next[2];

	d[0] = data->mob[i].mx - data->mob[j].mx;
	d[1] = data->mob[i].my - data->mob[j].my;
	dist = sqrtf(d[0] * d[0] + d[1] * d[1]);
	if (dist < 0.3f && dist > 0.0001f)
	{
		d[0] /= dist;
		d[1] /= dist;
		push = (0.3f - dist) * 0.1f;
		next[0] = data->mob[i].mx + d[0] * push;
		next[1] = data->mob[i].my + d[1] * push;
		if (!check_wall_collision(data, next[0], data->mob[i].my, 0.2f))
			data->mob[i].mx = next[0];
		if (!check_wall_collision(data, data->mob[i].mx, next[1], 0.2f))
			data->mob[i].my = next[1];
	}
}

static void	repel_mobs(t_data *data, int i)
{
	int	j;

	j = -1;
	while (++j < data->mob_count)
	{
		if (j == i || !data->mob[j].is_alive)
			continue ;
		apply_repulsion(data, i, j);
	}
}

void	mob_chase(t_data *data)
{
	int	i;

	if (data->game_on == 0)
		return ;
	i = -1;
	while (++i < data->mob_count)
	{
		if (data->mob[i].chase == 1 && data->mob[i].is_alive)
		{
			move_mob_toward(data, i);
			repel_mobs(data, i);
		}
	}
}

void	mob_path(t_data *data)
{
	int	i;
	int	distance;

	i = -1;
	while (++i < data->mob_count)
	{
		if (data->mob[i].is_alive)
		{
			distance = calculate_mob_distance(data, i);
			if (distance < 6)
				data->mob[i].chase = 1;
		}
	}
	mob_chase(data);
}

#endif