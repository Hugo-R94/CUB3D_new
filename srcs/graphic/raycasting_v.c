/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_v.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:13:42 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/26 13:52:18 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_vertical_ray(t_data *data, t_raycast *ray, float angle)
{
	ray->ntan = -tan(angle);
	if (angle > M_PI_2 && angle < 3 * M_PI_2)
	{
		ray->rx = (int)data->player.px - 0.0001f;
		ray->ry = (data->player.px - ray->rx) * ray->ntan + data->player.py;
		ray->xo = -1.0f;
	}
	else
	{
		ray->rx = (int)data->player.px + 1.0f;
		ray->ry = (data->player.px - ray->rx) * ray->ntan + data->player.py;
		ray->xo = 1.0f;
	}
	ray->yo = -ray->xo * ray->ntan;
}

void	cast_vertical_ray(t_data *data, float *rx, float *ry, float angle)
{
	t_raycast	ray;
	int			dof;

	init_vertical_ray(data, &ray, angle);
	dof = 0;
	while (dof < 100)
	{
		if (is_wall_hit(data, (int)ray.rx, (int)ray.ry))
			break ;
		ray.rx += ray.xo;
		ray.ry += ray.yo;
		dof++;
	}
	*rx = ray.rx;
	*ry = ray.ry;
}

#ifdef BONUS 

void	cast_vertical_door_ray(t_data *data, float *rx, float *ry, float angle)
{
	t_raycast	ray;
	int			dof;
	int			map_x;
	int			map_y;
	float		t;

	init_vertical_ray(data, &ray, angle);
	dof = -1;
	while (++dof < 25)
	{
		map_x = (int)ray.rx;
		map_y = (int)ray.ry;
		if (is_door_hit(data, map_x, map_y))
		{
			*rx = (float)map_x + 0.5f;
			t = (*rx - data->player.px) / cos(angle);
			*ry = data->player.py + t * sin(angle);
			return ;
		}
		ray.rx += ray.xo;
		ray.ry += ray.yo;
	}
	*rx = ray.rx;
	*ry = ray.ry;
}

void	cast_vertical_mob_ray(t_data *data, float *rx, float *ry, float angle)
{
	t_raycast	ray;
	int			dof;
	int			map_x;
	int			map_y;
	float		t;

	init_vertical_ray(data, &ray, angle);
	dof = -1;
	while (++dof < 15)
	{
		map_x = (int)ray.rx;
		map_y = (int)ray.ry;
		if (is_mob(data, map_x, map_y))
		{
			*rx = (float)map_x + 0.5f;
			t = (*rx - data->player.px) / cos(angle);
			*ry = data->player.py + t * sin(angle);
			return ;
		}
		ray.rx += ray.xo;
		ray.ry += ray.yo;
	}
	*rx = ray.rx;
	*ry = ray.ry;
}

#endif