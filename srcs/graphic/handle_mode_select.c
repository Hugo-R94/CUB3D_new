/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mode_select.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:15:32 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/03 14:18:16 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#ifdef BONUS
void do_nothing(t_data *data);

//le deuxieme bouton bug donc jai mis un bouton inutile en dehors de la fenetre
t_button	gmd_selector[] =
{
	{98, 92, 200, 125, "gamemode_mandatory", play_mandatory},
	{800,800,0,0,"fix", do_nothing},
	{342, 92, 200, 125, "gamemode_endless", play_endless_mode},
	// {320,50, 200, 125, "new_button", play_mandatory},
	{98, 262, 200, 125, "gamemode_survivor", play_survivor_mode},
	{342, 262, 200, 125, "gamemode_mainmenu", play_survivor_mode},
	{270, 410, 100, 50, "main menu", play_mainmenu},
	{0, 0, 0, 0, NULL, NULL}
};

void	play_mandatory(t_data *data)
{
	printf("madatory\n");
	new_map_random(data);
	data->current_pg = GAME_PG;
}
void do_nothing(t_data *data)
{
	if(data)
		return ;
	else 
		return ;
}

void	play_endless_mode(t_data *data)
{
	printf("endless mode\n");
	new_map_random(data);
	data->current_pg = GAME_PG;
}

void	play_survivor_mode(t_data *data)
{
	printf("survivor\n");
	new_map_random(data);
	data->current_pg = GAME_PG;
}

void	play_mainmenu(t_data *data)
{
	printf("main menu\n");
	data->current_pg = HOME_PG;
	data->current_buttons = g_home_button;
}

void	draw_game_mode(t_data	*data)
{
	int	pos[2];

	pos[0] = 85;
	pos[1] = 25;
	draw_rect(data, (int []){70, 12}, (int []){500, 50}, 0xFF0000);
	put_string_to_img(data, pos, 0x7D3322, "GAME MODE SELECTER");
	draw_rect(data, (int []){98, 92}, (int []){200, 125}, 0xE53412);
	draw_to_img(data, "button_200x125", 98, 92);
	draw_to_img(data, "button_200x125", 342, 92);
	draw_to_img(data, "button_200x125", 98, 262);
	draw_to_img(data, "button_200x125", 342, 262);
}
#endif