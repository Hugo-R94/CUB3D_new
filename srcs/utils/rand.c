/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:14:45 by hugz              #+#    #+#             */
/*   Updated: 2025/11/26 17:52:52 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdlib.h>
#include <time.h>

void	init_rand(void)
{
	srand(time(NULL));
}

int	get_rand_d(int min, int max)
{
	return (min + rand() % (max - min + 1));
}

float	get_rand_f(float min, float max)
{
	float	r ;

	r = (float)rand() / (float)RAND_MAX;
	return (min + r * (max - min));
}

char	get_rand_c(char *charset)
{
	int	range;

	range = 0;
	while (charset[range])
		range++;
	if (range <= 0)
		return ('\0');
	return (charset[rand() % range]);
}

void	calculate_fps(long *prev, float *fps, long current)
{
	if (*prev != 0)
		*fps = 1000.0f / (current - *prev);
	*prev = current;
}
