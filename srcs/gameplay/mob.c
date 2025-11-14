/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:59:07 by hugz              #+#    #+#             */
/*   Updated: 2025/11/14 14:38:15 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

static int check_wall_collision(t_data *data, float x, float y, float r)
{
	// Check les 4 coins de la hitbox
	if (data->map->map[(int)(y - r)][(int)(x - r)] == '1')
		return (1);
	if (data->map->map[(int)(y - r)][(int)(x + r)] == '1')
		return (1);
	if (data->map->map[(int)(y + r)][(int)(x - r)] == '1')
		return (1);
	if (data->map->map[(int)(y + r)][(int)(x + r)] == '1')
		return (1);
	return (0);
}

void move_mob_toward(t_data *data, int i)
{
	float dx, dy, dist, speed;
	float next_x, next_y;
	float r = 0.2f;
	
	speed = 0.05f;
	dx = data->player.px - data->mob[i].mx;
	dy = data->player.py - data->mob[i].my;
	dist = sqrtf(dx * dx + dy * dy);
	
	if (dist < 0.001f)
		return;
	
	dx /= dist;
	dy /= dist;
	
	next_x = data->mob[i].mx + dx * speed;
	next_y = data->mob[i].my + dy * speed;
	
	// Check collision avec les 4 coins
	if (!check_wall_collision(data, next_x, data->mob[i].my, r))
		data->mob[i].mx = next_x;
	
	if (!check_wall_collision(data, data->mob[i].mx, next_y, r))
		data->mob[i].my = next_y;
}

static void repel_mobs(t_data *data, int i)
{
	int j;
	float dx, dy, dist, push;
	float new_x, new_y;
	float r = 0.2f;  // Même rayon que la collision

	j = -1;
	while (++j < data->mob_count)
	{
		if (j == i || !data->mob[j].is_alive)
			continue;
		
		dx = data->mob[i].mx - data->mob[j].mx;
		dy = data->mob[i].my - data->mob[j].my;
		dist = sqrtf(dx * dx + dy * dy);
		
		if (dist < 0.3f && dist > 0.0001f)
		{
			dx /= dist;
			dy /= dist;
			push = (0.3f - dist) * 0.1f;
			
			// Nouvelle position après répulsion
			new_x = data->mob[i].mx + dx * push;
			new_y = data->mob[i].my + dy * push;
			
			// Vérifie les murs avant d'appliquer
			if (!check_wall_collision(data, new_x, data->mob[i].my, r))
				data->mob[i].mx = new_x;
			
			if (!check_wall_collision(data, data->mob[i].mx, new_y, r))
				data->mob[i].my = new_y;
		}
	}
}

void mob_chase(t_data *data)
{
	int i;

	if (data->game_on == 0)
		return;
	
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

void mob_path(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->mob_count)
	{
		if (data->mob[i].is_alive)
		{
			int distance = calculate_mob_distance(data, i);
			if (distance < 6)
				data->mob[i].chase = 1;
		}
	}
	mob_chase(data);
}

// void mob_path(t_data *data)
// {
//     for (int i = 0; i < data->mob_count; i++)
//     {
//         int distance = calculate_mob_distance(data, i);
//         if (distance < 6)
//             data->mob[i].chase = 1;
//     }
//     mob_chase(data);
// }


#endif