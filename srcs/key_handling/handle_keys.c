/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:40:00 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/10 12:59:36 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#ifdef BONUS
int	handle_key(int keycode, void *param)
{
	t_data	*data;
	return (0);
}

int	handle_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	clear_and_exit(data);
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
