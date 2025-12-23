/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:02:26 by mtangalv          #+#    #+#             */
/*   Updated: 2024/12/24 11:35:47 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	num_of_places(int n)
{
	if (n == INT_MIN)
		return (11);
	if (n < 0)
		return (num_of_places (-n) + 1);
	if (n < 10)
		return (1);
	return (1 + num_of_places (n / 10));
}

char	*ft_itoa(int n)
{
	char			*final;
	unsigned int	digits;
	unsigned int	num;

	digits = num_of_places(n);
	final = (char *)malloc(sizeof(char) * (digits + 1));
	if (final == NULL)
		return (NULL);
	num = n;
	if (n < 0)
	{
		final[0] = '-';
		num = -n;
	}
	if (num == 0)
		final[0] = '0';
	final[digits] = '\0';
	while (num != 0)
	{
		final[digits - 1] = (num % 10) + '0';
		num /= 10;
		digits--;
	}
	return (final);
}
