/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:08:59 by hugz              #+#    #+#             */
/*   Updated: 2025/11/14 18:13:21 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void knockback(t_data *data)
{
    float dx, dy, dist, force = 1.0f;
    int j;

    j = 0;
    while (j < data->mob_count)
    {
        if (data->mob[j].knockback && data->mob[j].is_alive)
        {
            dx = data->mob[j].mx - data->player.px;
            dy = data->mob[j].my - data->player.py;
            dist = sqrtf(dx * dx + dy * dy);

            if (dist < 0.01f) // évite div par zéro
                dist = 0.01f;

            // normalise le vecteur
            dx /= dist;
            dy /= dist;

            // applique knockback progressivement
            if (data->mob[j].knockback_timer < 10)
            {
                data->mob[j].mx += dx * force / 10.0f;
                data->mob[j].my += dy * force / 10.0f;
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
	int   i;
	float dx;
	float dy;
	float dist;
	float hit_radius = 0.3f; // BEAUCOUP plus grand !

	i = 0;
	while (i < data->mob_count)
	{
		if (!data->mob[i].is_alive) // Skip les mobs morts
		{
			i++;
			continue;
		}
		
		dx = data->player.px - data->mob[i].mx;
		dy = data->player.py - data->mob[i].my;
		dist = sqrtf(dx * dx + dy * dy);
		
		if (dist < hit_radius)
		{
			printf("Player hit! Distance: %f\n", dist);
			// Optionnel : cooldown pour éviter spam
			// data->mob[i].last_hit_time = current_time;
		}
		i++;
	}
}