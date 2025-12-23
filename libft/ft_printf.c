/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:19:20 by mtangalv          #+#    #+#             */
/*   Updated: 2025/02/08 11:01:44 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	printf_test(va_list flags, const char *string, int i, int *total)
{
	int	printed;

	printed = 0;
	if (string[i] == 'c')
		printed = ft_putchar(va_arg(flags, int));
	if (string[i] == 's')
		printed = ft_putstr(va_arg(flags, char *));
	if (string[i] == 'd' || string[i] == 'i')
		printed = ft_putnbr(va_arg(flags, int));
	if (string[i] == 'u')
		printed = ft_putnbr_u(va_arg(flags, unsigned int));
	if (string[i] == 'x' || string[i] == 'X')
		printed = ft_puthex(va_arg(flags, unsigned int), string[i], total);
	if (string[i] == 'p')
		printed = ft_putmem(va_arg(flags, size_t), total);
	if (string[i] == '%')
		printed = ft_putchar('%');
	if (printed == -1)
		return (-1);
	if (string[i] != 'x' || string[i] != 'X')
		*total += printed;
	return (0);
}

int	ft_printf(const char *string, ...)
{
	va_list	flags;
	int		i;
	int		total_chars;

	i = 0;
	total_chars = 0;
	va_start(flags, string);
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			i++;
			if (printf_test(flags, string, i, &total_chars) == -1)
				return (-1);
			i++;
		}
		else
		{
			if (ft_putchar(string[i]) == -1)
				return (-1);
			total_chars++;
			i++;
		}
	}
	return (total_chars);
}
