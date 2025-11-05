/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:34:27 by hrouchy           #+#    #+#             */
/*   Updated: 2025/04/28 10:38:27 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(char *s, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		s[index] = '\0';
		index++;
	}
	return (s);
}

// int main() {
//     char str1[20] = "TestString12345";
//     char str2[20] = "TestString12345";

//     // Utilisation de memset standard
//     bzero(str1, 5);

//     // Utilisation de ft_memset
//     ft_bzero(str2, 5);

//     // Affichage des résultats
//     printf("bzero   : %s\n", str1);
//     printf("ft_bzero: %s\n", str2);

//     // Comparaison avec memcmp
//     if (memcmp(str1, str2, sizeof(str1)) == 0) {
//         printf("✅ Les deux memset donnent le même résultat !\n");
//     } else {
//         printf("❌ Il y a une différence entre memset et ft_memset !\n");
//     }

//     return 0;
// }