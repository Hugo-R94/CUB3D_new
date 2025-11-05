/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:54:12 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/02 17:06:15 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_join;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str_join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str_join)
		return (NULL);
	str_join[0] = '\0';
	ft_strcat(str_join, s1);
	ft_strcat(str_join, s2);
	return (str_join);
}
