/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:23:20 by mtangalv          #+#    #+#             */
/*   Updated: 2025/05/13 12:31:44 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(const char *str)
{
	float	num;
	float	dec;
	char	*c;
	int		len;
	int		neg;

	c = (char *) str;
	neg = 1;
	num = (float)ft_atoi(c);
	if (*c++ == '-')
		neg = -1;
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	dec = (float)ft_atoi(c);
	len = ft_strlen(c);
	while (len--)
		dec /= 10;
	if (num >= 0)
		return ((num + dec) * neg);
	else
		return ((num + -dec) * neg);
}
