/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:40:00 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/20 13:22:31 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#ifdef BONUS
int	handle_key(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 38)
		resize_window(data, 640, 480);
	if (keycode == 233)
		resize_window(data, 1280, 960);
	if (keycode == 34)
		resize_window(data, 1920, 1440);
	if (keycode == 65436)
		data->current_pg = GMP_PG;
	if (keycode == 65433)
		data->current_pg = HOME_PG;
	if (keycode == 65435)
		data->current_pg = SETT_PG;
	else
		printf("key = %i\n", keycode);
	return (0);
}

int	handle_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	clean_and_exit(data, 0);
	return (0);	
}

#else
int	handle_key(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;

	printf("key = %i\n", keycode);
	return (0);
}
int handle_close(void *param)
{
    t_data *data = (t_data *)param;

	clean_exit_mand(data);
    return (0);
}

#endif
