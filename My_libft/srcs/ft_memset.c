/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:35:10 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/05 10:21:49 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, int size)
{
	int				index;
	unsigned char	*tmp;

	index = 0;
	tmp = (unsigned char *)s;
	while (index < size)
		tmp[index++] = c;
	return (tmp);
}

// int main() {
//     char str1[20] = "TestString12345";
//     char str2[20] = "TestString12345";
//
//     // Utilisation de memset standard
//     memset(str1, 'X', 5);
//
//     // Utilisation de ft_memset
//     ft_memset(str2, 'X', 5);
//
//     // Affichage des résultats
//     printf("memset   : %s\n", str1);
//     printf("ft_memset: %s\n", str2);
//
//     // Comparaison avec memcmp
//     if (memcmp(str1, str2, sizeof(str1)) == 0) {
//         printf("✅ Les deux memset donnent le même résultat !\n");
//     } else {
//         printf("❌ Il y a une différence entre memset et ft_memset !\n");
//     }
//
//     return 0;
// }