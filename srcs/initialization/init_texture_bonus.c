/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:51:39 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/27 14:06:27 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <string.h>

#ifdef BONUS

const char	*g_texture_names[]
	= {
	"HUD_placeholder",
	// "mettre_nom_txt_ici",
	"Home_bg",
	"Home_ash",
	"Home_title",
	"HUD",
	"black",
	"wall_wood",
	"slider_base",
	"exit",
	"bos",
	"slider_button",
	"wall",
	"button",
	"shot",
	"button_200x125",
	"Ash_100",
	"Ash_75",
	"hand_right",
	"hand_left",
	"skull",
	"cloud_1",
	"Ash_50",
	"Ash_25",
	"test",
	"cloud",
	"door",
	"wall_re",
	"door_close",
	"gamemode_endless",
	"ground",
	"mob",
	"gamemode_survivor",
	"aim",
	"gamemode_mandatory",
	"gamemode_mainmenu",
	"necronomicon",
	"pointeur",
	"skybox",
	"floor",
	// Lettres majuscules
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	// Chiffres
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	NULL
};

static void	free_textures_partial(t_txt *textures, int count)
{
	int	k;

	k = -1;
	while (++k < count)
	{
		free(textures[k].name);
		free(textures[k].path);
	}
	free(textures);
}

static int	init_texture_name(t_txt *textures, int j)
{
	textures[j].name = ft_strdup(g_texture_names[j]);
	if (!textures[j].name)
		return (0);
	textures[j].path = ft_sprintf("txt/%s.xpm", textures[j].name);
	if (!textures[j].path)
	{
		free(textures[j].name);
		return (0);
	}
	return (1);
}

t_txt	*init_paths(void)
{
	int		i;
	int		j;
	t_txt	*textures;

	i = 0;
	while (g_texture_names[i])
		i++;
	textures = ft_calloc(i + 1, sizeof(t_txt));
	if (!textures)
		return (NULL);
	j = -1;
	while (++j < i)
	{
		if (!init_texture_name(textures, j))
		{
			free_textures_partial(textures, j);
			return (NULL);
		}
	}
	textures[i].name = NULL;
	textures[i].path = NULL;
	return (textures);
}

static int	load_xpm_image(t_data *data, t_txt *txt)
{
	printf("%stxt name = %s | txt path = %s\n%s",
		GRN, txt->name, txt->path, RESET);
	txt->img.image = mlx_xpm_file_to_image(data->win->mlx,
			txt->path, &txt->img.width, &txt->img.height);
	if (!txt->img.image)
	{
		fprintf(stderr, "Erreur: impossible de charger %s\n", txt->path);
		return (0);
	}
	txt->img.data = mlx_get_data_addr(txt->img.image,
			&txt->img.bpp, &txt->img.size_line, &txt->img.format);
	return (1);
}

t_txt	*init_textures(t_data *data)
{
	t_txt	*textures;
	int		i;

	if (!data || !data->win || !data->win->mlx)
	{
		fprintf(stderr, "Erreur: MLX non initialisé!\n");
		return (NULL);
	}
	textures = init_paths();
	if (!textures)
		return (NULL);
	i = 0;
	while (textures[i].name)
	{
		if (!load_xpm_image(data, &textures[i]))
		{
			free_textures_partial(textures, i + 1);
			return (NULL);
		}
		i++;
	}
	return (textures);
}

#endif