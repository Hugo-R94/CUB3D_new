/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:33:16 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/07 10:58:32 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	character;

	character = (char)c;
	while (n > 0)
	{
		if (*(char *)s == character)
			return ((void *)s);
		n--;
		s++;
	}
	return ((void *) NULL);
}
