/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:41:51 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/13 17:04:11 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

/*
** Fonction à remplir : retourne la texture selon la lettre du mur
*/
static t_txt *get_texture_by_letter(t_data *data, char letter)
{
	if (letter == '1')
		return (find_texture(data->txt, "wall_re"));
	if (letter == '2')
	{
		// printf("cest un mur bois\n");
		return (find_texture(data->txt, "wall_re"));
	}
	if (letter == '3')
		return(find_texture(data->txt, "necronomicon"));
	else if (letter == 'D')
	{
		// printf("la cest une porte \n");
		return (find_texture(data->txt, "door"));
	}
	else if (letter == 'L')
	{
		// printf("la cest une porte ouverte\n");
		return (find_texture(data->txt, "door"));
	}
	else if (letter == 'M')
		return (find_texture(data->txt, "mob"));
	return (find_texture(data->txt, "black"));
}

/*
** Récupère la lettre du mur touché à partir des coordonnées
*/
char get_wall_letter(t_data *data, float rx, float ry)
{
	int mx;
	int my;
	int rowlen;
	char c;

	if (!data || !data->map || !data->map->map)
		return ('1');

	mx = (int)floorf(rx);
	my = (int)floorf(ry);

	if (data->map->height && (my < 0 || my >= (int)data->map->height))
		return ('1');

	if (my < 0)
		return ('1');
	rowlen = (int)strlen(data->map->map[my]);
	if (mx < 0 || mx >= rowlen)
		return ('1');

	c = data->map->map[my][mx];
	if (c == '\0')
		return ('1');
	return c;
}

/*
** Sélectionne la texture selon la direction ET la lettre du mur
*/
t_txt *find_wall_txt(t_data *data, float dist_h, float dist_v, 
							 float ra, float rx_h, float ry_h, 
							 float rx_v, float ry_v)
{
	int     base_index;
	char    wall_letter;
	t_txt   *texture;

	if (dist_h < dist_v)
	{
		wall_letter = get_wall_letter(data, rx_h, ry_h);
		if (sin(ra) > 0)
			base_index = 1;  // Sud (SO)
		else
			base_index = 0;  // Nord (NO)
	}
	else
	{
		wall_letter = get_wall_letter(data, rx_v, ry_v);
		if (cos(ra) > 0)
			base_index = 2;  // Est (EA)
		else
			base_index = 3;  // Ouest (WE)
	}
	texture = get_texture_by_letter(data, wall_letter);
	if (!texture && data->txt)
		texture = find_texture(data->txt, "south");
	
	return (texture);
}

/*
** Calcule la coordonnée X sur la texture
*/
float get_wall_x_coord(float dist_h, float dist_v,
							   float hit_x, float hit_y, float ra)
{
	float wall_x;

	if (dist_h < dist_v)
	{
		wall_x = hit_x - floor(hit_x);
		if (sin(ra) > 0)
			wall_x = 1.0f - wall_x;
	}
	else
	{
		wall_x = hit_y - floor(hit_y);
		if (cos(ra) < 0)
			wall_x = 1.0f - wall_x;
	}
	return (wall_x);
}

/*
** Convertit wall_x en coordonnée pixel de texture
*/
int get_texture_x(t_img *img, float wall_x)
{
	int tex_x;

	tex_x = (int)(wall_x * img->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= img->width)
		tex_x = img->width - 1;
	return (tex_x);
}



#endif