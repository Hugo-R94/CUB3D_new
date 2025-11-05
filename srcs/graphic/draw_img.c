/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:01:57 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/28 15:59:56 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	copy_texture_to_img(t_img *src, t_img *dst, int pos_x, int pos_y)
{
	int			x;
	int			y;
	int			dst_x;
	int			dst_y;
	uint32_t	color;

	y = -1;
	while (++y < src->height)
	{
		x = -1;
		while (++x < src->width)
		{
			color = get_pixel(src, x, y);
			dst_x = pos_x + x;
			dst_y = pos_y + y;
			if (dst_x < 0 || dst_y < 0 || dst_x >= dst->width
				|| dst_y >= dst->height)
				continue ;
			if (color != 0x000000)
				put_pixel(dst, dst_x, dst_y, color);
		}
	}
}

#ifdef BONUS

t_txt	*find_texture(t_txt *textures, const char *name)
{
	int	i;

	i = -1;
	if (!textures || !name)
		return (NULL);
	while (textures[++i].name)
		if (strcmp(textures[i].name, name) == 0)
			return (&textures[i]);
	return (NULL);
}

void	draw_to_img(t_data *data, const char *txt_name, int pos_x, int pos_y)
{
	t_txt	*txt;

	if (!data || !data->win || !data->win->img || !data->txt)
	{
		printf("Erreur : draw_to_img() paramètres invalides\n");
		return ;
	}
	txt = find_texture(data->txt, txt_name);
	if (!txt)
	{
		printf("Erreur : texture '%s' introuvable\n", txt_name);
		return ;
	}
	if (!txt->img.data)
	{
		printf("Erreur : texture '%s' non initialisée\n", txt_name);
		return ;
	}
	copy_texture_to_img(&txt->img, data->win->img, pos_x, pos_y);
}
#endif