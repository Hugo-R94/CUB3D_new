/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_gameplay.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:20:26 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/14 18:13:13 by hugz             ###   ########.fr       */
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
	draw_to_img(data,"aim", 308, 178);
	if (data->player.is_shooting)
		draw_to_img(data, "shot", 380, 180 + (data->player.pl_height * 1.2));
	if(!data->player.shoot_reload)
		draw_to_img(data,"hand_right", 400, 200 + (data->player.pl_height * 1.2));
	draw_to_img(data,"hand_left", -100, 200 - (data->player.pl_height * 1.2));
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
			// printf("depth = %d\n", fimg->pixels[index].depth);
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
		render->pixels[i].depth = -1;
		render->pixels[i].type = PX_EMPTY;
	}
}

void render_depth(t_f_img *f_img)
{
    int i;
    int gray;
    float depth;
    const float max_depth = 25.0f; // profondeur max

    for (i = 0; i < f_img->height * f_img->width; i++)
    {
        depth = f_img->pixels[i].depth;

        if (depth >= 0)
        {
            // Conversion linéaire renforcée
            gray = 255 - (int)((depth / max_depth) * 255);

            // On peut accentuer le contraste avec un carré (depth progressive)
            gray = (int)((gray / 255.0f) * (gray / 255.0f) * 255);

            // Clamp
            if (gray < 0) gray = 0;
            if (gray > 255) gray = 255;

            // Couleur en niveaux de gris
            f_img->pixels[i].color = (gray << 16) | (gray << 8) | gray;
        }
    }
}
uint32_t darken_color2(uint32_t color, float depth)
{
    uint8_t r, g, b;
    float   factor;
    
    if (depth < 0.0f)
        depth = 0.0f;
    if (depth > 1.0f)
        depth = 1.0f;
    
    factor = 1.0f - depth;
    
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
    
    r = (uint8_t)(r * factor);
    g = (uint8_t)(g * factor);
    b = (uint8_t)(b * factor);
    
    return ((r << 16) | (g << 8) | b);
}

uint32_t pp_px_depth(uint32_t color, float depth)
{
    float factor;
    
    if (depth <= 0)
        return (color);
    
    // Assombrissement progressif de plus en plus rapide
    if (depth <= 4.0f)
        factor = depth / 25.0f;                    // Linéaire doux
    // else if (depth <= 12.0f)
    //     factor = (depth * depth) / 400.0f;         // Quadratique
    else if (depth <= 20.0f)
        factor = (depth * depth) / 300.0f;         // Quadratique plus rapide
    else
        factor = 1.0f;                             // Noir complet
    
    if (factor > 1.0f)
        factor = 1.0f;
    
    return (darken_color2(color, factor));
}

void pp_depth(t_f_img *f_img)
{
    int i;
    
    i = 0;
    while (i < f_img->height * f_img->width)
    {
        if (f_img->pixels[i].depth >= 0)
            f_img->pixels[i].color = pp_px_depth(f_img->pixels[i].color, 
                                                   f_img->pixels[i].depth);
        i++;
    }
}

void	render_px_type(t_f_img *f_img)
{
	int i;

	i = 0;
	// printf("renderpxtype\n");
	while (i < f_img->height * f_img->width)
	{
		if (f_img->pixels[i].type == PX_MOB)
			f_img->pixels[i].color = 0xFF0000;
		else if (f_img->pixels[i].type == PX_WALL)
			f_img->pixels[i].color = 0x00FF00;
		else
			f_img->pixels[i].color = 0x0000FF;
		i++;
	}
}

void	render_px_type_mob(t_f_img *f_img)
{
	int i;

	i = 0;
	// printf("renderpxtype\n");
	while (i < f_img->height * f_img->width)
	{
		if (f_img->pixels[i].type == PX_MOB)
			f_img->pixels[i].color = 0xFF0000;
		i++;
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
	// render_depth(data->render_gmp);
	// pp_depth(data->render_gmp);
	render_px_type_mob(data->render_gmp);
	int cx = data->render_gmp->width / 2;
	int cy = data->render_gmp->height / 2;
	int index = cy * data->render_gmp->width + cx;
	// data->render_gmp->pixels[data->render_gmp->height * data->render_gmp->width / 2].color = 0xFF0000;
	// if (data->render_gmp->pixels[index].type == PX_MOB)
	// 	printf("viseur sur un mob\n");
	shooting(data);
	knockback(data);
	draw_final_image(data,0,0);
	draw_hand_pl(data);
	is_player_hit(data);
	render_hud_still(data);
	render_hud_infos(data);
	// printf("game on ? = %d | in game ? = %d | button = %d\n",data->game_on, data->in_game, data->current_buttons);
}
#endif