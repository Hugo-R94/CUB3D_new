/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:55:39 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/27 13:43:41 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS

/* Fonction pour calculer et dessiner le mur */
static void	process_wall(t_data *data, int i, float ra, float *dist_final)
{
	t_raycast	raycast;
	float		dists[2];
	int			dims[2];
	t_txt		*txt;

	raycast.ra = ra;
	cast_rays(data, &raycast);
	calculate_distances(data, &raycast, &dists[0], &dists[1]);
	get_final_distance(data, (float []){dists[0], dists[1]}, ra, dist_final);
	calculate_wall_dimensions(data, *dist_final,
		(int *[]){&dims[0], &dims[1]}, 1);
	get_texture_info(data, dists, &raycast, &txt);
	store_ray_coords(data, i, &raycast, dists);
	render_column(data, (int []){i, dims[1], dims[0], dims[1], raycast.tex_x},
		txt, *dist_final);
}

/* Fonction pour ajuster les dimensions de la porte */
static void	adjust_door_dimensions(int *line_h, int *line_off)
{
	int	original_bottom;

	original_bottom = *line_off + *line_h;
	*line_off = original_bottom - *line_h;
}

/* Fonction pour calculer et dessiner la porte */
static void	process_door(t_data *data, int i, float ra, float wall_dist)
{
	t_raycast	door_ray;
	float		dists[3];
	int			dims[2];
	t_txt		*txt;

	door_ray.ra = ra;
	cast_doors_rays(data, &door_ray);
	calculate_distances(data, &door_ray, &dists[0], &dists[1]);
	get_final_distance(data, (float []){dists[0], dists[1]}, ra, &dists[2]);
	if (dists[2] > 0 && dists[2] < wall_dist)
	{
		store_ray_coords(data, i, &door_ray, dists);
		calculate_wall_dimensions(data, dists[2],
			(int *[]){&dims[0], &dims[1]}, 1);
		adjust_door_dimensions(&dims[0], &dims[1]);
		get_texture_info(data, dists, &door_ray, &txt);
		draw_door_column(data, (int []){i, dims[1], dims[0], dims[1],
			door_ray.tex_x}, &txt->img, dists[2]);
	}
}

/* Fonction principale */
static void	process_single_ray(t_data *data, int i, float ra)
{
	float	wall_dist;

	process_wall(data, i, ra, &wall_dist);
	process_door(data, i, ra, wall_dist);
}

void	render_gameplay(t_data *data)
{
	float	ra;
	int		i;

	if (!data || !data->map || !data->map->map)
	{
		printf("la y pas de map\n");
		return ;
	}
	i = 0;
	while (i < 640)
	{
		ra = data->player.pa - (data->fov / 2) + (data->fov * i) / 640;
		while (ra < 0)
			ra += 2 * M_PI;
		while (ra >= 2 * M_PI)
			ra -= 2 * M_PI;
		process_single_ray(data, i, ra);
		i++;
	}
	draw_mobs(data);
	draw_exit(data);
}
#endif