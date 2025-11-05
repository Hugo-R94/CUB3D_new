/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:34:21 by hrouchy           #+#    #+#             */
/*   Updated: 2025/04/29 10:09:44 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

// int main()
// {
//     char test_chars[] = {'a', 'Z', '1', ' ', 'm', 'N', '9', '\n'};
//     for (int i = 0; i < sizeof(test_chars); i++) {
//         printf("ft_isalpha('%c') = %d\n",
//			 test_chars[i], ft_isalpha(test_chars[i]));
//     }
//     return 0;
// }