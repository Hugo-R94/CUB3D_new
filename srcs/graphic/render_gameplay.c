/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_gameplay.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:20:26 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/13 17:26:26 by hugz             ###   ########.fr       */
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

void draw_hand_pl(t_data *data)
{
	if (data->mouse.mouse_pressed)
		draw_to_img(data, "shot", 380, 180 + (data->player.pl_height * 1.2));
	draw_to_img(data,"hand_right", 400, 200 + (data->player.pl_height * 1.2));
	draw_to_img(data,"hand_left", -100, 200 - (data->player.pl_height * 1.2));
}

void	render_gameplay(t_data *data)
{
	draw_walls_3d(data);
	draw_hand_pl(data);
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

void    animate_door(t_data *data)
{
    static int timer = 0;  // 1 = fermeture, -1 = ouverture
    int y;
	int x;

    if (data->door_state == 1)  // Ouvrir (monter)
    {
        if (data->offset_door_ratio < 1.0)
            data->offset_door_ratio += 0.1;
		timer += 1;
		if(timer >= 75)
		{
			timer = 0;
			data->door_state = 0;
		}		
    }
    else  // Fermer (descendre)
    {
        if (data->offset_door_ratio >= 0.0)
            data->offset_door_ratio -= 0.1;
		y = 0;
		while (data->map->map[y])
		{
			x = 0;
			while (data->map->map[y][x])
			{
				if (data->map->map[y][x] == 'L')
					data->map->map[y][x] = 'D';
					x++;
			}
			y++;
		}
    }
	if (data->offset_door_ratio < 0)
		data->offset_door_ratio = 0;
}
void	draw_final_image(t_data *data, int pos_x, int pos_y)
{
	t_f_img	*fimg;
	int		x;
	int		y;
	int		index;

	fimg = data->render_gmp;
	y = 0;
	while (y < 480)
	{
		x = 0;
		while (x < 640)
		{
			index = y * fimg->width + x;
			// put_pixel(&data->win->img, pos_x + x, pos_y + y,
				// fimg->pixels[index].color);
			put_pixel(data->win->img, pos_x + x, pos_y + y, fimg->pixels[index].color);
			x++;
		}
		y++;
	}
}
void clear_render_gmp(t_f_img *render)
{
	int total = render->width * render->height;
	for (int i = 0; i < total; i++)
	{
		render->pixels[i].color = 0x000000;
		render->pixels[i].depth = INT_MAX;
		render->pixels[i].type = PX_EMPTY;
	}
}

void	render_gameplay_full(t_data *data)
{
	// data->current_pg = GAME_PG;
	// printf("render gameplay\n");
	clear_render_gmp(data->render_gmp);
	data->current_buttons = g_no_button;
	if (data->current_pg == GAME_PG)
		data->game_on = 1;
	data->in_game = 1;
	mob_path(data);
	mouv_player(data);
	draw_ceiling_img(data);
	animate_door(data);
	render_gameplay(data);
	draw_to_img(data,"aim", 308, 178);
	draw_final_image(data,0,0);
	render_hud_still(data);
	render_hud_infos(data);
	// printf("game on ? = %d | in game ? = %d | button = %d\n",data->game_on, data->in_game, data->current_buttons);
}
#endif