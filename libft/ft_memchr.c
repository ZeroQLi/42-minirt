/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:50:13 by mtangalv          #+#    #+#             */
/*   Updated: 2024/12/24 11:36:11 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	l;
	unsigned char	*to_str;

	to_str = (unsigned char *)str;
	l = (unsigned char) c;
	while (n-- > 0)
	{
		if (to_str[0] == l)
			return ((char *) to_str);
		to_str++;
	}
	return (NULL);
}
