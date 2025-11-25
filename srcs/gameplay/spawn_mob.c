/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_mob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:26:40 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 12:27:10 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

static void	spawn_mob_at_position(t_data *data, int idx)
{
	float	ra;
	float	dist;
	t_mob	*mob;

	mob = &data->mob[data->mob_count + idx];
	memset(mob, 0, sizeof(t_mob));
	mob->chase = 1;
	mob->hp = 2;
	mob->is_alive = 1;
	mob->knockback_timer = 0;
	mob->knockback = 0;
	mob->size = get_rand_f(0.7, 1.2);
	mob->id = idx;
	mob->sprite = "mob";
	ra = get_rand_f(0, 2 * M_PI);
	dist = get_rand_f(3, 5);
	mob->mx = data->player.px + cos(ra) * dist;
	mob->my = data->player.py + sin(ra) * dist;
}

static int	allocate_mobs(t_data *data, int count)
{
	t_mob	*new_mobs;

	new_mobs = realloc(data->mob, sizeof(t_mob) * (data->mob_count + count));
	if (!new_mobs)
		return (0);
	data->mob = new_mobs;
	return (1);
}

void	spawn_random_mob(t_data *data)
{
	static int		timer = 0;
	static float	difficulty = 1.0;
	int				count;
	int				i;

	if (++timer < 300)
		return ;
	count = get_rand_d(2 * (int)difficulty, 3 * (int)difficulty);
	if (!allocate_mobs(data, count))
		return ;
	i = -1;
	while (++i < count)
		spawn_mob_at_position(data, i);
	data->mob_count += count;
	difficulty += 0.3;
	timer = 0;
}

#endif