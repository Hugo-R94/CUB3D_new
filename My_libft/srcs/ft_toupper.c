/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:37:22 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/02 12:04:06 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int i)
{
	if (i >= 'a' && i <= 'z')
		i = i - 32;
	return (i);
}

// int main(void)
// {
//     char test[] = "abcABC123!@#";
//     int i = 0;

//     while (test[i])
//     {
//         printf("%c -> %c\n", test[i], ft_toupper(test[i]));
//         i++;
//     }
//     return (0);
// }
