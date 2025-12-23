/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:32:44 by mtangalv          #+#    #+#             */
/*   Updated: 2025/02/08 11:01:40 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_base(char c)
{
	if (c == 'x')
		return ("0123456789abcdef");
	else
		return ("0123456789ABCDEF");
}

int	ft_puthex(unsigned int num, char c, int *printed)
{
	char			*base;
	int				i;
	char			string[25];

	i = 0;
	base = check_base(c);
	if (num == 0)
	{
		if (ft_printf("%d", 0) == -1)
			return (-1);
		return (1);
	}
	while (num != 0)
	{
		string[i++] = base [num % 16];
		num /= 16;
	}
	*printed += i;
	while (i--)
	{
		if (ft_printf("%c", string[i]) == -1)
			return (-1);
	}
	return (0);
}

static int	check_zero_mem(size_t num, int *p)
{
	if (num == 0)
	{
		if (ft_printf("0") == -1)
			return (-1);
		*p += 1;
	}
	return (0);
}

int	ft_putmem(size_t num, int *printed)
{
	char			*base;
	int				i;
	char			string[25];

	i = 0;
	base = "0123456789abcdef";
	if (ft_printf("0x") == -1)
		return (-1);
	*printed += 2;
	if (check_zero_mem(num, printed) == -1)
		return (-1);
	while (num != 0)
	{
		string[i++] = base [num % 16];
		num /= 16;
		(*printed)++;
	}
	while (i--)
	{
		if (ft_putchar(string[i]) == -1)
			return (-1);
	}
	return (0);
}
