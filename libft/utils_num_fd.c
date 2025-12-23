/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_num_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:43:20 by mtangalv          #+#    #+#             */
/*   Updated: 2025/04/25 16:40:21 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

int	ft_putnbr_u_fd(unsigned int n, int fd)
{
	int	digits;

	digits = 0;
	if (n >= 10)
	{
		if (ft_putnbr_fd(n / 10, fd) == -1)
			return (-1);
	}
	if (ft_putchar_fd(n % 10 + '0', fd) == -1)
		return (-1);
	digits += num_places_u(n);
	return (digits);
}
