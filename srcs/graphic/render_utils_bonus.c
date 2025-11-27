/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:41:51 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/27 13:31:04 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

/*
** Fonction à remplir : retourne la texture selon la lettre du mur
*/
static t_txt	*get_texture_by_letter(t_data *data, char letter)
{
	if (letter == '1')
		return (find_texture(data->txt, "wall"));
	if (letter == '2')
		return (find_texture(data->txt, "wall"));
	if (letter == '3')
		return (find_texture(data->txt, "necronomicon"));
	else if (letter == 'D')
		return (find_texture(data->txt, "door"));
	else if (letter == 'L')
		return (find_texture(data->txt, "door"));
	else if (letter == 'M')
		return (find_texture(data->txt, "mob"));
	return (find_texture(data->txt, "black"));
}

/*
** Récupère la lettre du mur touché à partir des coordonnées
*/
char	get_wall_letter(t_data *data, float rx, float ry)
{
	int		mx;
	int		my;
	int		rowlen;
	char	c;

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
	return (c);
}

/*
// ** Sélectionne la texture selon la direction ET la lettre du mur
// */
t_txt	*find_wall_txt(t_data *data, float dist_h, float dist_v, t_raycast *ray)
{
	char	wall_letter;
	t_txt	*texture;

	if (dist_h < dist_v)
	{
		wall_letter = get_wall_letter(data, ray->rx_h, ray->ry_h);
	}
	else
	{
		wall_letter = get_wall_letter(data, ray->rx_v, ray->ry_v);
	}
	texture = get_texture_by_letter(data, wall_letter);
	if (!texture && data->txt)
		texture = find_texture(data->txt, "south");
	return (texture);
}

float	get_wall_x_coord(float dist_h, float dist_v,
							float hit[2], float ra)
{
	float	wall_x;

	if (dist_h < dist_v)
	{
		wall_x = hit[0] - floor(hit[0]);
		if (sin(ra) > 0)
			wall_x = 1.0f - wall_x;
	}
	else
	{
		wall_x = hit[1] - floor(hit[1]);
		if (cos(ra) < 0)
			wall_x = 1.0f - wall_x;
	}
	return (wall_x);
}

/*
** Convertit wall_x en coordonnée pixel de texture
*/
int	get_texture_x(t_img *img, float wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * img->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= img->width)
		tex_x = img->width - 1;
	return (tex_x);
}

#endif