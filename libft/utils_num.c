/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:43:20 by mtangalv          #+#    #+#             */
/*   Updated: 2025/02/08 11:01:36 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_places(int n)
{
	int	r;

	r = 1;
	while (n > 9)
	{
		n /= 10;
		r++;
	}
	return (r);
}

static int	num_places_u(unsigned int n)
{
	int	r;

	r = 1;
	while (n > 9)
	{
		n /= 10;
		r++;
	}
	return (r);
}

int	ft_putnbr(int n)
{
	int	digits;

	digits = 0;
	if (n == INT_MIN)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
		return (11);
	}
	if (n < 0)
	{
		if (ft_putchar ('-') == -1)
			return (-1);
		n = -n;
		digits++;
	}
	if (n >= 10)
	{
		if (ft_putnbr (n / 10) == -1)
			return (-1);
	}
	if (ft_putchar(n % 10 + '0') == -1)
		return (-1);
	digits += num_places(n);
	return (digits);
}

int	ft_putnbr_u(unsigned int n)
{
	int	digits;

	digits = 0;
	if (n >= 10)
	{
		if (ft_putnbr (n / 10) == -1)
			return (-1);
	}
	if (ft_putchar(n % 10 + '0') == -1)
		return (-1);
	digits += num_places_u(n);
	return (digits);
}
