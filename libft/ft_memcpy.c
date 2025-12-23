/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:56:57 by mtangalv          #+#    #+#             */
/*   Updated: 2025/02/07 19:27:51 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *to, const void *from, size_t numBytes)
{
	size_t	i;

	i = 0;
	if (to != from)
	{
		while (i < numBytes)
		{
			((unsigned char *)to)[i] = ((unsigned char *)from)[i];
			i++;
		}
	}
	return (to);
}
