/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:28:53 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/04 11:22:44 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include "ft_printf.h"
#include <limits.h>

int	ft_idformat(va_list args, char *str, int index)
{
	int	char_count;

	char_count = 0;
	if (str[index] != '%')
		return (0);
	if (str[index + 1] == 'c')
		char_count = ft_putchar(va_arg(args, int));
	if (str[index + 1] == 's')
		char_count = ft_putstr(va_arg(args, char *));
	if (str[index + 1] == 'p')
		char_count = ft_putptr(va_arg(args, char *));
	if (str[index + 1] == 'i')
		char_count = ft_putnb(va_arg(args, int));
	if (str[index + 1] == 'd')
		char_count = ft_putnb(va_arg(args, int));
	if (str[index + 1] == 'u')
		char_count = ft_putunsigned(va_arg(args, int));
	if (str[index + 1] == 'x')
		char_count = ft_puthexa(va_arg(args, unsigned int), 0);
	if (str[index + 1] == 'X')
		char_count = ft_puthexa(va_arg(args, unsigned int), 1);
	if (str[index + 1] == '%')
		char_count = ft_putchar('%');
	return (char_count);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		index;
	int		char_count;
	char	*format;

	format = (char *)s;
	va_start(args, s);
	index = 0;
	char_count = 0;
	while (format[index])
	{
		if (format[index] == '%' && format[index + 1])
		{
			char_count += ft_idformat(args, format, index);
			index += 2;
		}
		else
		{
			ft_putchar(format[index]);
			char_count++;
			index++;
		}
	}
	va_end(args);
	return (char_count);
}

int	ft_putptr(void *ptr)
{
	int	count;

	if (!ptr)
	{
		ft_putstr("(nil)");
		return (5);
	}
	count = 0;
	count += ft_putstr("0x");
	count += ft_puthexa((uintptr_t)ptr, 0);
	return (count);
}
