/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:08:59 by hugz              #+#    #+#             */
/*   Updated: 2025/11/19 18:40:36 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void knockback(t_data *data)
{
    float dx, dy, dist, force = 2.0f;
    int j = 0;

    while (j < data->mob_count)
    {
        if (data->mob[j].knockback && data->mob[j].is_alive)
        {
            dx = data->mob[j].mx - data->player.px;
            dy = data->mob[j].my - data->player.py;
            dist = sqrtf(dx * dx + dy * dy);

            if (dist < 0.01f)
                dist = 0.01f;

            dx /= dist;
            dy /= dist;

            float mvx = dx * force / 10.0f;
            float mvy = dy * force / 10.0f;

            if (data->mob[j].knockback_timer < 10)
            {
                // --- Vérification mur pour X ---
                float next_x = data->mob[j].mx + mvx;
                if (data->map->map[(int)data->mob[j].my][(int)next_x] != '1')
                    data->mob[j].mx = next_x;

                // --- Vérification mur pour Y ---
                float next_y = data->mob[j].my + mvy;
                if (data->map->map[(int)next_y][(int)data->mob[j].mx] != '1')
                    data->mob[j].my = next_y;

                data->mob[j].knockback_timer++;
            }
            else
            {
                data->mob[j].knockback = 0;
                data->mob[j].knockback_timer = 0;
            }
        }
        j++;
    }
}

void is_player_hit(t_data *data)
{
    int i = 0;
    float dx, dy, dist;
    float hit_radius = 0.1f;
    float force = 0.15f;

    while (i < data->mob_count)
    {
        if (!data->mob[i].is_alive)
        {
            i++;
            continue;
        }

        dx = data->player.px - data->mob[i].mx;
        dy = data->player.py - data->mob[i].my;
        dist = sqrtf(dx * dx + dy * dy);

        if (dist < hit_radius && data->mob[i].knockback == 0)
        {
            printf("Player hit! Distance: %f\n", dist);

            data->mob[i].knockback = 1;
            if (dist < 0.01f)
                dist = 0.01f;

            dx /= dist;
            dy /= dist;

            float mvx = dx * force;
            float mvy = dy * force;

            float next_x = data->player.px + mvx;
            float next_y = data->player.py + mvy;

            // --- Collision X ---
            if (data->map->map[(int)data->player.py][(int)next_x] != '1')
                data->player.px = next_x;

            // --- Collision Y ---
            if (data->map->map[(int)next_y][(int)data->player.px] != '1')
                data->player.py = next_y;
        }
        i++;
    }
}
