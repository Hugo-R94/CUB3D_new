/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:33:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/05 14:15:57 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ss1;
	unsigned char	*ss2;
	size_t			i;

	i = 0;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (i < n)
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	return (0);
}
// int main() {
//     char str1[] = "Hello, world!";
//     char str2[] = "Hello, world!";
//     char str3[] = "Hello, friend!";

//     size_t size = 10; // Nombre d'octets à comparer

//     // Test avec memcmp
//     int result_memcmp = memcmp(str1, str3, size);
//     printf("memcmp    : %d\n", result_memcmp);

//     // Test avec ft_memcmp
//     int result_ft_memcmp = ft_memcmp(str2, str3, size);
//     printf("ft_memcmp : %d\n", result_ft_memcmp);

//     return 0;
// }

// int main()
// {
// 	size_t size = 3;
// 	char *b1 = malloc(size-1);
// 	char *b2 = malloc(size-1);

// 	strcpy(b1, ".........");
// 	strcpy(b2, ".........");
// 	printf("%s\n",b1);
// 	printf("%s\n",b2);
// 	printf("%i",ft_memcmp(b1, b2, size));
// }
