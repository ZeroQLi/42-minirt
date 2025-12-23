/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:46:22 by mtangalv          #+#    #+#             */
/*   Updated: 2024/12/24 15:51:39 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_sep(char const c, char const *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		size;
	char	*final;

	if (!s1 || !set)
		return (NULL);
	while (s1)
	{
		if (check_sep(((char)*s1), set) == 1)
			s1++;
		else
			break ;
	}
	size = ft_strlen(s1);
	while (size != 0)
	{
		if (check_sep(s1[size - 1], set) == 1)
			size--;
		else
			break ;
	}
	final = (char *)malloc(sizeof(char) * (size + 1));
	if (final == NULL)
		return (0);
	ft_strlcpy(final, (char *)s1, (size + 1));
	return (final);
}
