/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:59:07 by hugz              #+#    #+#             */
/*   Updated: 2025/11/13 17:23:45 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS
void move_mob_toward(t_data *data, int i)
{
    float dx, dy, dist;
    float speed;
    float next_x, next_y;

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
    if (data->map->map[(int)data->mob[i].my][(int)next_x] != '1')
        data->mob[i].mx = next_x;
    if (data->map->map[(int)next_y][(int)data->mob[i].mx] != '1')
        data->mob[i].my = next_y;
}

static void repel_mobs(t_data *data, int i)
{
	int j;
	float dx;
    float dy;
    float dist;
	float push;

	j = -1;
    while (++j < data->mob_count)
    {
        if (j == i)
            continue;

        dx = data->mob[i].mx - data->mob[j].mx;
        dy = data->mob[i].my - data->mob[j].my;
        dist = sqrtf(dx * dx + dy * dy);
        if (dist < 0.3f && dist > 0.0001f)
        {
            dx /= dist;
            dy /= dist;
            float push = (0.3f - dist) * 0.1f; 
            data->mob[i].mx += dx * push;
            data->mob[i].my += dy * push;
        }
    }
}
void mob_chase(t_data *data)
{
    if (data->game_on == 0)
        return; // aucun mob ne bouge si le jeu est en pause

    for (int i = 0; i < data->mob_count; i++)
    {
        if (data->mob[i].chase == 1)
        {
            move_mob_toward(data, i);
            repel_mobs(data, i);
        }
    }
}


void mob_path(t_data *data)
{
    for (int i = 0; i < data->mob_count; i++)
    {
        int distance = calculate_mob_distance(data, i);
        if (distance < 6)
            data->mob[i].chase = 1;
    }
    mob_chase(data);
}


#endif