/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:48:15 by hugz              #+#    #+#             */
/*   Updated: 2025/11/25 13:14:19 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#ifdef BONUS

void	handle_shoot_start(t_data *data, t_pl *p)
{
	if (!data->mouse.mouse_button_rc)
		return ;
	if (p->is_shooting)
		return ;
	if (p->shoot_cd != 0)
		return ;
	if (p->shoot_reload != 0)
		return ;
	p->is_shooting = 1;
	p->shoot_timer = 0;
}

void	process_shoot_hit(t_data *data, int *bullet_had_hitted)
{
	int		cx;
	int		cy;
	int		index;
	t_px	*px;

	cx = data->render_gmp->width / 2;
	cy = data->render_gmp->height / 2;
	if (cx < 0 || cx >= data->render_gmp->width)
		return ;
	if (cy < 0 || cy >= data->render_gmp->height)
		return ;
	index = cy * data->render_gmp->width + cx;
	px = &data->render_gmp->pixels[index];
	if (px->type != PX_MOB)
		return ;
	if (*bullet_had_hitted != 0)
		return ;
	if (px->id < 0 || px->id >= data->mob_count)
		return ;
	data->mob[px->id].hp -= 1;
	data->mob[px->id].knockback = 1;
	*bullet_had_hitted = 1;
}

void	handle_shoot_end(t_data *data, t_pl *p, int *bullet_had_hitted)
{
	if (!p->is_shooting)
		return ;
	if (p->shoot_timer <= 10)
		return ;
	p->is_shooting = 0;
	p->shoot_timer = 0;
	data->player.bullet_count++;
	if (data->player.bullet_count >= 2)
	{
		p->shoot_reload = 1;
		p->shoot_reload_timer = 0;
	}
	else
	{
		p->shoot_cd = 1;
		p->shoot_cd_timer = 0;
	}
	*bullet_had_hitted = 0;
}

void	update_cooldown(t_pl *p)
{
	if (p->is_shooting)
		return ;
	if (!p->shoot_cd)
		return ;
	p->shoot_cd_timer++;
	if (p->shoot_cd_timer > 5)
	{
		p->shoot_cd_timer = 0;
		p->shoot_cd = 0;
	}
}

void	shooting(t_data *data)
{
	static int	bullet_had_hitted = 0;
	t_pl		*p;

	p = &data->player;
	if (!data->render_gmp || !data->render_gmp->pixels)
		return ;
	handle_shoot_start(data, p);
	if (p->is_shooting && p->shoot_timer <= 10)
	{
		process_shoot_hit(data, &bullet_had_hitted);
		p->shoot_timer++;
	}
	handle_shoot_end(data, p, &bullet_had_hitted);
	update_cooldown(p);
	if (p->is_shooting)
		return ;
	if (!p->shoot_reload)
		return ;
	p->shoot_reload_timer++;
	if (p->shoot_reload_timer > 25)
	{
		p->shoot_reload_timer = 0;
		p->shoot_reload = 0;
		data->player.bullet_count = 0;
	}
}
#endif
