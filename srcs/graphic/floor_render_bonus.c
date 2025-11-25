/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_render_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:37:41 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/20 15:03:08 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef BONUS

/* --- Calcule la distance au sol pour une ligne y donnée --- */
static float	get_row_distance(int y, double tilt)
{
	double	p;
	double	pos_z;
	double	row_dist;

	p = (y - (240 + tilt));
	if (p == 0)
		p = 1;
	pos_z = 240.0;
	row_dist = pos_z / p;
	return (row_dist);
}

/* --- Calcule la direction du rayon pour la colonne x --- */
static void	get_ray_dir(double *ray_x, double *ray_y, t_data *data, int x)
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	camera_x = 2.0 * x / 640.0 - 1.0;
	dir_x = cos(data->player.pa);
	dir_y = sin(data->player.pa);
	plane_x = -sin(data->player.pa) * tan(data->fov / 2);
	plane_y = cos(data->player.pa) * tan(data->fov / 2);
	*ray_x = dir_x + plane_x * camera_x;
	*ray_y = dir_y + plane_y * camera_x;
}

/* --- Calcule la position monde du point du sol --- */
static void	get_floor_pos(double *fx, double *fy, t_data *data, double *ray)
{
	double	row_dist;

	row_dist = ray[2];
	*fx = data->player.px + row_dist * ray[0];
	*fy = data->player.py + row_dist * ray[1];
}

/* --- Convertit position monde en coordonnées de texture --- */
static void	get_tex_coords(int *tex_x, int *tex_y, double *floor, t_img *img)
{
	int	cell_x;
	int	cell_y;

	cell_x = (int)floor[0];
	cell_y = (int)floor[1];
	*tex_x = (int)(img->width * (floor[0] - cell_x)) & (img->width - 1);
	*tex_y = (int)(img->height * (floor[1] - cell_y)) & (img->height - 1);
}

static void draw_floor_pix(t_data *data, int x, int y, t_txt *floor)
{
    double ray[3];
    double floor_pos[2];
    int tex[2];
    uint32_t color;
    int index;
    float depth;

    // Vérifier que x et y sont valides
    if (x < 0 || x >= data->render_gmp->width)
        return;
    if (y < 0 || y >= data->render_gmp->height)
        return;

    get_ray_dir(&ray[0], &ray[1], data, x);
    depth = get_row_distance(y, data->tilt + data->player.pl_height);
    ray[2] = depth;
    get_floor_pos(&floor_pos[0], &floor_pos[1], data, ray);
    get_tex_coords(&tex[0], &tex[1], floor_pos, &floor->img);

    color = get_pixel(&floor->img, tex[0], tex[1]);

    if (color != 0x000000)
    {
        index = y * data->render_gmp->width + x;

        data->render_gmp->pixels[index].color = color;
        data->render_gmp->pixels[index].depth = depth;
        data->render_gmp->pixels[index].type = PX_EMPTY;
    }
}


/* --- Fonction principale : dessine le sol pour la colonne x --- */
void	draw_floor(t_data *data, int x, int y_start)
{
	t_txt	*floor;
	int		y;

	floor = find_texture(data->txt, "floor");
	if (!floor || !floor->img.data)
		return ;
	y = y_start;
	while (y < 480)
	{
		draw_floor_pix(data, x, y, floor);
		y++;
	}
}

#endif
