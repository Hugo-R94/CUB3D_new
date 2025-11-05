/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:34:21 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/02 15:19:54 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, int size)
{
	int	index;

	index = 0;
	if (size == 0)
		return (0);
	if (size < 0)
		return (-1);
	while (s1[index] == s2[index] && index < size && s1[index])
		index++;
	if (index == size)
		return (0);
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}

// int main()
// {
//     char string1[] = "1234";
//     char string2[] = "1235";
//     int size_n = -568654;
//     printf("strncmp    = %d \n",strncmp(string1,string2,size_n));
//     printf("ft_strncmp = %d \n",ft_strncmp(string1,string2,size_n));
// }