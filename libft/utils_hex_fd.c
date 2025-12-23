/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:32:44 by mtangalv          #+#    #+#             */
/*   Updated: 2025/04/25 16:39:47 by mtangalv         ###   ########.fr       */
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

int	ft_puthex_fd(unsigned int num, char c, int *printed, int fd)
{
	char			*base;
	int				i;
	char			string[25];

	i = 0;
	base = check_base(c);
	if (num == 0)
	{
		if (ft_dprintf(fd, "%d", 0) == -1)
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
		if (ft_dprintf(fd, "%c", string[i]) == -1)
			return (-1);
	}
	return (0);
}

static int	check_zero_mem(size_t num, int *p, int fd)
{
	if (num == 0)
	{
		if (ft_dprintf(fd, "0") == -1)
			return (-1);
		*p += 1;
	}
	return (0);
}

int	ft_putmem_fd(size_t num, int *printed, int fd)
{
	char			*base;
	int				i;
	char			string[25];

	i = 0;
	base = "0123456789abcdef";
	if (ft_dprintf(fd, "0x") == -1)
		return (-1);
	*printed += 2;
	if (check_zero_mem(num, printed, fd) == -1)
		return (-1);
	while (num != 0)
	{
		string[i++] = base [num % 16];
		num /= 16;
		(*printed)++;
	}
	while (i--)
	{
		if (ft_putchar_fd(string[i], fd) == -1)
			return (-1);
	}
	return (0);
}
