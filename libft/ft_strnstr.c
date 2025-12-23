/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:38:58 by mtangalv          #+#    #+#             */
/*   Updated: 2024/12/24 11:37:20 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (needle[i] == '\0' || needle == NULL)
		return ((char *) haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[n])
		{
			while (haystack[i + n] == needle[n] && i + n < len)
			{
				if (needle[n + 1] == '\0')
					return ((char *) haystack + i);
				n++;
			}
			n = 0;
		}
		i++;
	}
	return (0);
}
