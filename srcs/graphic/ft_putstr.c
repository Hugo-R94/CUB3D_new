/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:09:05 by hugz              #+#    #+#             */
/*   Updated: 2025/10/17 12:26:47 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#ifdef BONUS
/* --- Copie d'une lettre sur l'image principale --- */
void	cop_l_to_img(t_img *src, t_img *dst, int pos[2], uint32_t p_col)
{
	int			x;
	int			y;
	uint32_t	color;
	int			dst_x;
	int			dst_y;

	y = -1;
	while (++y < src->height)
	{
		x = -1;
		while (++x < src->width)
		{
			color = get_pixel(src, x, y);
			dst_x = pos[0] + x;
			dst_y = pos[1] + y;
			if (dst_x < 0 || dst_y < 0 || dst_x >= dst->width
				|| dst_y >= dst->height)
				continue ;
			if (color == 0x00000)
				put_pixel(dst, dst_x, dst_y, p_col);
		}
	}
}

/* --- Dessine une lettre (depuis ton dossier alphabet) --- */
void	draw_letter(t_data *data, char *str, int pos[2], uint32_t print_colour)
{
	char	txt_name[32];
	t_txt	*txt;

	if (!data || !data->win || !data->win->img || !data->txt)
	{
		printf("Erreur : draw_letter() paramètres invalides\n");
		return ;
	}
	txt = find_texture(data->txt, str);
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
	cop_l_to_img(&txt->img, data->win->img, pos, print_colour);
}

/* --- Affiche une chaîne entière à partir d'un alphabet XPM --- */
void	put_string_to_img(t_data *data, int pos[2], uint32_t color, char *str)
{
	int		i;
	int		x;
	int		y;
	int		letter_pos[2];
	char	letter[2];

	if (!data || !str)
		return ;
	x = pos[0];
	y = pos[1];
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			x += 25;
			i++;
		}
		else
		{
			letter[0] = str[i];
			letter[1] = '\0';
			letter_pos[0] = x;
			letter_pos[1] = y;
			draw_letter(data, letter, letter_pos, color);
			x += 25;
			i++;
		}
	}
}
#endif