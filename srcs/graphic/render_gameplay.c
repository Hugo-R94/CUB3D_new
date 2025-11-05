/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_gameplay.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:20:26 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/04 13:53:04 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#ifdef BONUS
t_button g_no_button[] =
{
	{0, 0, 0, 0, NULL, NULL}
};

void	render_hud_still(t_data *data)
{
	int		pos[2];
	char	*hp;

	pos[0] = 70;
	pos[1] = data->pos_y_hud + 350;
	if (data)
		printf("");
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
	// draw_mini_map(data, 350, data->pos_y_hud + 175);
	draw_mini_map_centered(data, 75, 5, (int[]){450, data->pos_y_hud + 250});
	

	//render non mouvable part of hud
	// draw_to_img(data,const)
 }

void	render_hud_infos(t_data *data)
{
	//render mouvable part of hud
	if (data)
		printf("");
	
}
void	render_gameplay(t_data *data)
{
	draw_walls_3d(data);
	// draw_to_img(data, "test", 0, 0);
	// render cub3D
}

// char *return_page_id(t_page_id id)
// {
// 	if (id == HOME_PG)
// 		return("HOME PAGE");
// 	if (id == HOME_PG)
// 		return("HOME PAGE");
// 	if (id == HOME_PG)
// 		return("HOME PAGE");
// 	if (id == HOME_PG)
// 		return("HOME PAGE");
// }

void	render_gameplay_full(t_data *data)
{
	// data->current_pg = GAME_PG;
	// printf("render gameplay\n");
	data->current_buttons = g_no_button;
	data->game_on = 1;
	data->in_game = 1;
	
	mouv_player(data);
	draw_ceiling_img(data);
	
	render_gameplay(data);
	render_hud_still(data);
	render_hud_infos(data);
	// printf("game on ? = %d | in game ? = %d | button = %d\n",data->game_on, data->in_game, data->current_buttons);
}
#endif