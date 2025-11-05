/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:58:49 by hrouchy           #+#    #+#             */
/*   Updated: 2025/10/13 11:41:31 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdarg.h>
#include <stdlib.h>

static int	handle_percent_i(char *res, int j, va_list args)
{
	char	*tmp;
	int		k;

	tmp = ft_itoa(va_arg(args, int));
	if (!tmp)
		return (j);
	k = 0;
	while (tmp[k])
		res[j++] = tmp[k++];
	free(tmp);
	return (j);
}

static int	handle_percent_s(char *res, int j, va_list args)
{
	char	*tmp;
	int		k;

	tmp = va_arg(args, char *);
	if (!tmp)
		tmp = "(null)";
	k = 0;
	while (tmp[k])
		res[j++] = tmp[k++];
	return (j);
}

void	build_sprintf(char *res, const char *format, va_list args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == 'i')
		{
			j = handle_percent_i(res, j, args);
			i += 2;
		}
		else if (format[i] == '%' && format[i + 1] == 's')
		{
			j = handle_percent_s(res, j, args);
			i += 2;
		}
		else
			res[j++] = format[i++];
	}
	res[j] = '\0';
}

char	*ft_sprintf(const char *format, ...)
{
	va_list	args;
	char	*res;

	res = malloc(sizeof(char) * 100);
	if (!res)
		return (NULL);
	va_start(args, format);
	build_sprintf(res, format, args);
	va_end(args);
	return (res);
}

void	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	char	*res;

	res = ft_calloc(1000, sizeof(char));
	if (!res)
		return ;
	va_start(args, format);
	build_sprintf(res, format, args);
	va_end(args);
	ft_putstr_fd(res, fd);
	free(res);
}
