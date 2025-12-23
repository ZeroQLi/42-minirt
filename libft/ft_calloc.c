/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:55:10 by mtangalv          #+#    #+#             */
/*   Updated: 2024/12/26 10:13:09 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	size_t	num;
	void	*tmp;

	if (nitems == 0 || size == 0)
		nitems = 0;
	num = nitems * size;
	tmp = malloc(num);
	if (tmp == NULL)
		return (NULL);
	else
		ft_bzero(tmp, num);
	return (tmp);
}
