/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:13:36 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/29 12:43:50 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	render_frame_mandatory(t_data *data)
{
	struct timeval	st;
	struct timeval	end;
	long			elapsed;
	long			frame_time_us;
	int				fps;

	frame_time_us = 33333;
	gettimeofday(&st, NULL);
	mouv_player(data);
	draw_walls_3d(data);
	draw_mini_map(data, 25, 25);
	gettimeofday(&end, NULL);
	elapsed = (end.tv_sec - st.tv_sec) * 1000000L + (end.tv_usec - st.tv_usec);
	fps = 1000000 / elapsed;
	if (fps > 30)
		usleep(frame_time_us - elapsed);
	mlx_put_image_to_window(data->win->mlx, data->win->win,
		data->win->img, 0, 0);
	mlx_string_put(data->win->mlx, data->win->win,50,50,0xFF0000, ft_itoa(fps));
	return (0);
}

void	gameloop_mand(t_data *data)
{
	mlx_loop_hook(data->win->mlx, render_frame_mandatory, data);
	mlx_hook(data->win->win, 17, 0, handle_close, data);
	mlx_hook(data->win->win, 2, 1L << 0, handle_key_press, data);
	mlx_hook(data->win->win, 3, 1L << 1, handle_key_release, data);
	mlx_loop(data->win->mlx);
}

void	check_parsing(t_data *data)
{
	if (!data->map->c_color || !data->map->f_color)
	{
		printf("Missing floor or ceiling color.\n");
		clean_exit_mand(data);
		exit(1);
	}
	if (!data->map->map)
	{
		printf("Missing map on file.\n");
		clean_exit_mand(data);
		exit(1);
	}
	if (!data->map->textures[0].path || !data->map->textures[1].path
		|| !data->map->textures[2].path || !data->map->textures[3].path)
	{
		printf("Missing texture(s) at the start of file.\n");
		clean_exit_mand(data);
	}
}

static void	init_game_data(t_data *data, int fd)
{
	int	len;

	data->map = parse_file(fd);
	check_parsing(data);
	if (!data->map->map)
		fprintf(stderr,
			"⚠️ Attention : data->map->map est NULL, aucune map chargée.\n");
	data->map->height = 0;
	data->map->width = 0;
	while (data->map->map[data->map->height])
	{
		len = ft_strlen(data->map->map[data->map->height]);
		if (len > data->map->width)
			data->map->width = len;
		data->map->height++;
	}
	init_textures_mand(data);
	close(fd);
	check_map_ff(data, data->map);
	get_player_original_pos(data);
}

int	main(int ac, char **av)
{
	int		fd;
	t_data	*data;

	fd = check_arg_and_open(ac, av);
	if (fd < 0)
		return (1);
	data = init_data();
	init_game_data(data, fd);
	gameloop_mand(data);
	clean_exit_mand(data);
	return (0);
}
