/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:33:34 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/13 10:54:41 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t			index;
	unsigned char	*source;
	unsigned char	*destination;

	source = (unsigned char *)src;
	destination = (unsigned char *)dest;
	index = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (index < size)
	{
		destination[index] = source[index];
		index++;
	}
	return (destination);
}

// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>
// int main() 
// {
//     char src[20] = "sssfrgwrgfdsg";
//     char dest1[] = "";
//     char dest2[] = "";
//     int size = 10;
//     // // Test avec la fonction standard
//     memcpy(dest1, src, size);
//     // Test avec ft_memmove
//     ft_memcpy(dest2, src, size);
//     // Affichage des résultats
//     printf("memcpy   : %s\n", dest1);
//     printf("ft_memcpy: %s\n", dest2);
//     // Vérification avec memcmp
//     if (memcmp(dest1, dest2, size) == 0) {
//         printf("✅ Les deux memcpy donnent le même résultat !\n");
//     } else {
//         printf("❌ Il y a une différence entre memcpy et ft_memcpy !\n");
//     }
//     return 0;
// }