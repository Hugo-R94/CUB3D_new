/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:34:13 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/07 11:16:21 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, int size)
{
	int				index;
	unsigned char	*source;
	unsigned char	*destination;

	source = (unsigned char *)src;
	destination = (unsigned char *)dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (destination > source && destination < source + size)
	{
		index = size;
		while (index-- > 0)
			destination[index] = source[index];
	}
	else
	{
		index = 0;
		while (index < size)
		{
			destination[index] = source[index];
			index++;
		}
	}
	return (destination);
}

// int main() {
//     char src[20] = "memmove test";
//     char *dest1 = 0;
//     char *dest2 = 0;

//     int size = 5;

//     // // Test avec la fonction standard
//     // memmove(((void*)0), ((void*)0), size);

//     // Test avec ft_memmove
//     ft_memmove(((void*)0), ((void*)0), size);

//     // Affichage des résultats
//     printf("memmove   : %s\n", dest1);
//     printf("ft_memmove: %s\n", dest2);

//     // Vérification avec memcmp
//     if (memcmp(dest1, dest2, size) == 0) {
//         printf("✅ Les deux memmove donnent le même résultat !\n");
//     } else {
//         printf("❌ Il y a une différence entre memmove et ft_memmove !\n");
//     }

//     return 0;
// }