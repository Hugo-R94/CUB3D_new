/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:14:45 by hugz              #+#    #+#             */
/*   Updated: 2025/11/19 11:33:24 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdio.h>
#include <sys/time.h>


int get_rand_d(int min, int max)
{
	struct timeval time;
	long rand;
	int range;

	range = max - min + 1;
	if (range <= 0)
		return (-1);
	gettimeofday(&time, NULL);
	rand = (time.tv_usec + 83);
	return (min + (rand % range));
}

float get_rand_f(float min, float max)
{
    struct timeval	time;
    float			range;
	float			rand;

    range = max - min;
    if (range <= 0)
        return (-1);
    gettimeofday(&time, NULL);
    rand = (float)(time.tv_usec % 1000000) / 1000000.0f;
    return (min + rand * range);
}

char	get_rand_c(char *charset)
{
	int		range;
	struct	timeval time;
	int		rand;	

	range = 0;
	while (charset[range])
		range++;
	if(range <= 0)
		return ('\0');
	gettimeofday(&time, NULL);
	rand = (time.tv_usec) % range;
	return(charset[rand]);
}

// int main(void)
// {
// 	int i; 
// 	float f;
// 	char charset[5] = "afiou";
// 	char rand_c;

// 	i = get_rand_d(0, 100);
// 	printf("int = %i\n",i);
// 	f = get_rand_f(1.5, 3.4);
// 	printf("float = %f\n",f);
// 	rand_c = get_rand_c(charset);
// 	printf("char = %c\n", rand_c);
// }