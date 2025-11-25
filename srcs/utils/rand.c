/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:14:45 by hugz              #+#    #+#             */
/*   Updated: 2025/11/24 14:39:09 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdlib.h>
#include <time.h>

void init_rand(void)
{
    srand(time(NULL));
}

int get_rand_d(int min, int max)
{
    return (min + rand() % (max - min + 1));
}

float get_rand_f(float min, float max)
{
    float r ;

	r = (float)rand() / (float)RAND_MAX;
    return (min + r * (max - min));
}


char get_rand_c(char *charset)
{
    int range;

	range = 0;
    while (charset[range])
        range++;
    if (range <= 0)
        return '\0';
    return (charset[rand() % range]);
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