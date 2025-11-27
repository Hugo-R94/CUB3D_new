/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_gameplay.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:20:26 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/27 14:58:21 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS

t_button	g_no_button[]
	= {
{0, 0, 0, 0, NULL, NULL}
};

void	render_hud_still(t_data *data)
{
	int		pos[2];
	char	*hp;

	pos[0] = 70;
	pos[1] = data->pos_y_hud + 350;
	draw_to_img(data, "HUD", 0, data->pos_y_hud);
	if (data->player_hp > 75)
		draw_to_img(data, "Ash_100", 50, data->pos_y_hud + 150);
	else if (data->player_hp > 50)
		draw_to_img(data, "Ash_75", 50, data->pos_y_hud + 150);
	else if (data->player_hp > 25)
		draw_to_img(data, "Ash_50", 50, data->pos_y_hud + 150);
	else
		draw_to_img(data, "Ash_25", 50, data->pos_y_hud + 150);
	put_string_to_img(data, pos, 0xFF0000, "HP");
	pos[0] += 70;
	hp = ft_itoa(data->player_hp);
	put_string_to_img(data, pos, 0xFF0000, hp);
	free(hp);
	draw_mini_map_centered(data, 75, 5, (int []){450, data->pos_y_hud + 250});
}

void	draw_final_image(t_data *data, int pos_x, int pos_y)
{
	t_f_img	*fimg;
	int		x;
	int		y;
	int		index;

	if (!data || !data->render_gmp || !data->render_gmp->pixels)
		return ;
	fimg = data->render_gmp;
	y = -1;
	while (++y < fimg->height)
	{
		x = -1;
		while (++x < fimg->width)
		{
			index = y * fimg->width + x;
			if ((pos_x + x) < 0 || (pos_x + x) >= data->win->img->width
				|| (pos_y + y) < 0 || (pos_y + y) >= data->win->img->height)
				continue ;
			put_pixel(data->win->img, pos_x + x, pos_y + y,
				fimg->pixels[index].color);
		}
	}
}

void	clear_render_gmp(t_f_img *render)
{
	int	total;
	int	i;

	total = render->width * render->height;
	i = -1;
	while (++i < total)
	{
		render->pixels[i].color = 0x000000;
		render->pixels[i].depth = -1;
		render->pixels[i].type = PX_EMPTY;
	}
}

// spawn_random_mob(data);
void	render_ingame(t_data *data)
{
	mob_path(data);
	mouv_player(data);
	draw_ceiling_img(data);
	animate_door(data);
	render_gameplay(data);
	pp_depth(data->render_gmp);
	shooting(data);
	use_chainsaw(data);
	knockback(data);
}

void	render_gameplay_full(t_data *data)
{
	data->current_buttons = g_no_button;
	if (data->current_pg == GAME_PG)
		data->game_on = 1;
	data->in_game = 1;
	if (data->game_on)
		render_ingame(data);
	draw_final_image(data, 0, 0);
	draw_to_img(data, "aim", 308, 178);
	if (data->player.is_shooting)
		draw_to_img(data, "shot", 380, 180 + (data->player.pl_height * 1.2));
	if (!data->player.shoot_reload)
		draw_to_img(data, "hand_right", 400, 200
			+ (data->player.pl_height * 1.2));
	draw_to_img(data, "hand_left", -125 + data->player.chainsaw_offset,
		225 - (data->player.pl_height * 1.2) - data->player.chainsaw_offset);
	is_player_hit(data);
	render_hud_still(data);
	monitor_player(data);
}
#endif