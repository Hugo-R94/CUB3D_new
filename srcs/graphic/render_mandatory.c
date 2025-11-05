/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mandatory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:01:42 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/03 11:17:28 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifndef BONUS

/*
** Sélectionne la texture du mur selon la direction du rayon et le type de collision.
** - dist_h < dist_v : collision horizontale (murs Nord/Sud)
**   - sin(ra) > 0 : rayon va vers le sud → texture SO
**   - sin(ra) < 0 : rayon va vers le nord → texture NO
** - dist_v < dist_h : collision verticale (murs Est/Ouest)
**   - cos(ra) > 0 : rayon va vers l'est → texture EA
**   - cos(ra) < 0 : rayon va vers l'ouest → texture WE
*/
t_txt	*find_wall_txt(t_data *data, float dist_h, float dist_v, float ra)
{
	if (dist_h < dist_v)
	{
		if (sin(ra) > 0)
			return (&data->map->textures[1]);
		else
			return (&data->map->textures[0]);
	}
	else
	{
		if (cos(ra) > 0)
			return (&data->map->textures[2]);
		else
			return (&data->map->textures[3]);
	}
}

/* ========================================================================== */
/*                           CALCULS DE DISTANCE                              */
/* ========================================================================== */

/*
** Calcule la distance euclidienne entre deux points (x1,y1) et (x2,y2).
** Formule : sqrt((x2-x1)² + (y2-y1)²)
*/
static float	calculate_distance(float x1, float y1, float x2, float y2)
{
	float	dx;
	float	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrtf(dx * dx + dy * dy));
}

/*
** Lance les rayons horizontal et vertical, puis calcule leurs distances.
** Les fonctions cast_horizontal_ray et cast_vertical_ray trouvent les points
** d'intersection du rayon avec la grille dans les deux directions.
*/
static void	get_distances(t_data *data, float ra, float *dist_h, float *dist_v)
{
	float	rx_h;
	float	ry_h;
	float	rx_v;
	float	ry_v;

	cast_horizontal_ray(data, &rx_h, &ry_h, ra);
	cast_vertical_ray(data, &rx_v, &ry_v, ra);
	*dist_h = calculate_distance(data->player.px, data->player.py, rx_h, ry_h);
	*dist_v = calculate_distance(data->player.px, data->player.py, rx_v, ry_v);
}

/* ========================================================================== */
/*                         CALCULS DE PROJECTION                              */
/* ========================================================================== */

/*
** Corrige l'effet fisheye en multipliant par le cosinus de la différence
** d'angle entre la direction du joueur et le rayon.
** Sans cette correction, les murs sur les côtés paraissent courbes.
** La distance minimale de 0.1 évite les divisions par zéro.
*/
static float	get_corrected_distance(t_data *data, float ra,
				float dist_h, float dist_v)
{
	float	dist_final;

	dist_final = fmin(dist_h, dist_v);
	dist_final *= cos(data->player.pa - ra);
	if (dist_final < 0.1f)
		dist_final = 0.1f;
	return (dist_final);
}

/*
** Calcule la hauteur du mur à l'écran.
** 1. Calcule plane_dist : distance du joueur au plan de projection
**    Formule : (largeur_écran / 2) / tan(fov / 2)
** 2. Hauteur du mur = plane_dist / distance_au_mur
** 3. Sauvegarde la hauteur complète AVANT clipping (pour le calcul du step)
** 4. Clippe la hauteur à res_y si nécessaire
*/
static int	calculate_line_height(t_data *data, float dist_final, int *full_h)
{
	float	plane_dist;
	int		line_h;

	plane_dist = (data->res_x / 2.0f) / tan(data->fov / 2.0f);
	line_h = (int)(plane_dist / dist_final);
	*full_h = line_h;
	if (line_h > data->res_y)
		line_h = data->res_y;
	return (line_h);
}

/* ========================================================================== */
/*                      CALCULS DE TEXTURE - POSITION X                       */
/* ========================================================================== */

/*
** Calcule la coordonnée X sur la texture (0.0 à 1.0).
** Pour les murs horizontaux : utilise hit_x (coordonnée X du point d'impact)
** Pour les murs verticaux : utilise hit_y (coordonnée Y du point d'impact)
** L'inversion (1.0 - wall_x) corrige l'orientation selon la direction du rayon.
*/
static float	get_wall_x_coord(float dist_h, float dist_v,
				float hit_x, float hit_y, float ra)
{
	float	wall_x;

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
** Convertit wall_x (0.0-1.0) en coordonnée pixel de texture.
** Multiplie par la largeur de l'image et clippe aux bords.
*/
static int	get_texture_x(t_img *img, float wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * img->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= img->width)
		tex_x = img->width - 1;
	return (tex_x);
}

/* ========================================================================== */
/*                           RENDU D'UNE COLONNE                              */
/* ========================================================================== */

/*
** Dessine un pixel de texture sur le mur.
** tex_pos indique quelle ligne de texture utiliser (position Y dans la texture).
** Après avoir dessiné, on incrémente tex_pos de step pour passer à la ligne suivante.
*/
static void	draw_wall_texture(t_data *data, t_img *img,
				int x, int y, int tex_x, float *tex_pos)
{
	int		tex_y;
	int		color;
	float	step;

	step = *tex_pos;
	tex_y = (int)step;
	color = get_pixel(img, tex_x, tex_y);
	put_pixel(data->win->img, x, y, color);
}

/*
** Dessine le plafond au-dessus du mur (de start_y à y).
*/
static void	draw_ceiling(t_data *data, int x, int start_y, int y)
{
	int	current_y;

	current_y = start_y;
	while (current_y < y)
	{
		put_pixel(data->win->img, x, current_y, data->map->c_color);
		current_y++;
	}
}

/*
** Dessine le sol en dessous du mur (de y à res_y).
*/
static void	draw_floor(t_data *data, int x, int y)
{
	int	current_y;

	current_y = y;
	while (current_y < data->res_y)
	{
		put_pixel(data->win->img, x, current_y, data->map->f_color);
		current_y++;
	}
}

/*
** Structure pour les paramètres de rendu.
*/
typedef struct s_render_params
{
	int		line_off;
	int		y;
	int		y_end;
	float	tex_pos;
	float	step;
}	t_render_params;

/*
** Initialise les paramètres de rendu de la colonne.
** - Calcule line_off : position verticale de départ du mur
** - Si le mur dépasse l'écran par le haut (line_off < 0),
**   on ajuste tex_pos pour commencer au milieu de la texture
** - step : combien de pixels de texture on parcourt par pixel d'écran
**   IMPORTANT : calculé avec full_line_h (hauteur non clippée) pour éviter
**   la compression de texture quand on est proche du mur
*/
static void	init_render_params(t_data *data, t_render_params *p,
				t_img *img, int full_line_h)
{
	p->step = (float)img->height / full_line_h;
	p->line_off = (data->res_y - full_line_h) / 2;
	if (p->line_off < 0)
	{
		p->tex_pos = (-p->line_off) * p->step;
		p->y = 0;
	}
	else
	{
		p->tex_pos = 0.0f;
		p->y = p->line_off;
	}
	p->y_end = p->line_off + full_line_h;
	if (p->y_end > data->res_y)
		p->y_end = data->res_y;
}

/*
** Dessine une colonne verticale complète (plafond + mur + sol).
** 1. Initialise les paramètres (offset, step, position texture)
** 2. Dessine le plafond
** 3. Dessine le mur pixel par pixel avec la texture
** 4. Dessine le sol
*/
static void	render_column(t_data *data, t_img *img,
				int x, int tex_x, int full_line_h)
{
	t_render_params	p;

	init_render_params(data, &p, img, full_line_h);
	draw_ceiling(data, x, 0, p.y);
	while (p.y < p.y_end)
	{
		draw_wall_texture(data, img, x, p.y, tex_x, &p.tex_pos);
		p.tex_pos += p.step;
		p.y++;
	}
	draw_floor(data, x, p.y);
}

/* ========================================================================== */
/*                    FONCTION PRINCIPALE DE RENDU TEXTURE                    */
/* ========================================================================== */

/*
** Calcule le point d'impact exact du rayon sur le mur.
** IMPORTANT : utilise dist_raw (distance NON corrigée du fisheye) car
** le point d'impact réel ne change pas, seule la projection change.
*/
static void	calculate_hit_point(t_data *data, float ra,
				float dist_raw, float *hit_x, float *hit_y)
{
	*hit_x = data->player.px + dist_raw * cos(ra);
	*hit_y = data->player.py + dist_raw * sin(ra);
}

/*
** Fonction principale qui coordonne le rendu d'une colonne de mur texturé.
** Étapes :
** 1. Trouve la bonne texture selon la direction
** 2. Calcule la distance brute et corrigée
** 3. Calcule la hauteur du mur (clippée et complète)
** 4. Calcule le point d'impact sur le mur
** 5. Détermine quelle colonne de texture utiliser (tex_x)
** 6. Rend la colonne complète
*/
void	draw_wall_column_txt(t_data *data, int x,
			float dist_h, float dist_v, float ra)
{
	t_txt	*txt;
	float	dist_final;
	float	dist_raw;
	int		full_line_h;
	float	hit_x;
	float	hit_y;
	float	wall_x;
	int		tex_x;

	txt = find_wall_txt(data, dist_h, dist_v, ra);
	dist_raw = fmin(dist_h, dist_v);
	dist_final = get_corrected_distance(data, ra, dist_h, dist_v);
	calculate_line_height(data, dist_final, &full_line_h);
	calculate_hit_point(data, ra, dist_raw, &hit_x, &hit_y);
	wall_x = get_wall_x_coord(dist_h, dist_v, hit_x, hit_y, ra);
	tex_x = get_texture_x(&txt->img, wall_x);
	render_column(data, &txt->img, x, tex_x, full_line_h);
}

/* ========================================================================== */
/*                         TRAITEMENT D'UN RAYON                              */
/* ========================================================================== */

/*
** Traite un seul rayon : calcule les distances et rend la colonne.
*/
static void	process_single_ray(t_data *data, int i, float ra)
{
	float	dist_h;
	float	dist_v;

	get_distances(data, ra, &dist_h, &dist_v);
	draw_wall_column_txt(data, i, dist_h, dist_v, ra);
}

/* ========================================================================== */
/*                            BOUCLE PRINCIPALE                               */
/* ========================================================================== */

/*
** Fonction principale de rendu 3D.
** Pour chaque colonne de l'écran (i de 0 à res_x) :
** 1. Calcule l'angle du rayon :
**    - Part de pa - fov/2 (bord gauche du champ de vision)
**    - Ajoute un incrément proportionnel à i
** 2. Normalise l'angle entre 0 et 2π
** 3. Traite le rayon pour dessiner la colonne
*/
void	draw_walls_3d(t_data *data)
{
	float	ra;
	int		i;

	if (!data || !data->map || !data->map->map)
		return ;
	i = 0;
	while (i < data->res_x)
	{
		ra = data->player.pa - (data->fov / 2) + (data->fov * i) / data->res_x;
		ra = normalize_angle(ra);
		process_single_ray(data, i, ra);
		i++;
	}
}

#endif