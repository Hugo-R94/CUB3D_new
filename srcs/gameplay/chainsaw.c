/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chainsaw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:37:28 by hugz              #+#    #+#             */
/*   Updated: 2025/11/24 17:23:34 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS 

void	process_chainsaw_hit(t_data *data, int *chainsaw_had_hitted)
{
	int		cx;
	int		cy;
	int		index;
	t_px	*px;

	cx = data->render_gmp->width / 2;
	cy = data->render_gmp->height / 2;
	if (*chainsaw_had_hitted != 0)
		return ;
	index = cy * data->render_gmp->width + cx;
	px = &data->render_gmp->pixels[index];
	if (px->type == PX_MOB)
	{
		if (px->depth < 1.2)
		{
			data->mob[px->id].hp -= 1;
			data->mob[px->id].knockback = 2;
			*chainsaw_had_hitted = 1;
			return ;
		}
	}
}

void	animate_chainsaw_forward(t_data *data, int *timer, int var[2],
								int *chainsaw_had_hitted)
{
	if (*timer < var[0])
		data->player.chainsaw_offset += var[1];
	*timer = *timer + 1;
	if (*timer == var[0] / 2)
	{
		process_chainsaw_hit(data, chainsaw_had_hitted);
	}
}

static void	chainsaw_backward(t_data *data, int *timer,
			int *using, int var[2])
{
	if (*timer < var[0])
		data->player.chainsaw_offset -= var[1];
	*timer = *timer + 1;
	if (*timer >= var[0])
	{
		*using = 0;
		*timer = 0;
		data->player.chainsaw_offset = 0;
	}
}

void	animate_chainsaw(t_data *data, int *timer, int *using,
					int *chainsaw_had_hitted)
{
	int			timing;
	int			offset;
	static int	pole = 1;

	timing = 3;
	offset = 12;
	if (pole == 1)
	{
		animate_chainsaw_forward(data, timer, (int []){timing, offset},
			chainsaw_had_hitted);
		if (*timer >= timing)
		{
			*timer = 0;
			pole = -1;
		}
	}
	else if (pole == -1)
	{
		chainsaw_backward(data, timer, using, (int []){timing, offset});
		if (*timer == 0)
			pole = 1;
	}
}

void	use_chainsaw(t_data *data)
{
	static int	timer = 0;
	static int	using = 0;
	static int	cooldown = 0;
	static int	chainsaw_had_hitted = 0;

	if (cooldown > 0)
		cooldown--;
	if (data->mouse.mouse_button_lc)
	{
		if (using == 0 && cooldown == 0)
			using = 1;
	}
	if (using == 1)
	{
		animate_chainsaw(data, &timer, &using, &chainsaw_had_hitted);
		if (using == 0)
		{
			cooldown = 10;
			chainsaw_had_hitted = 0;
		}
	}
}

#endif