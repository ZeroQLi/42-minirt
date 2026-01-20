/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:09:32 by mtangalv          #+#    #+#             */
/*   Updated: 2026/01/20 21:52:13 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_tuple	add_tuples(t_tuple a, t_tuple b)
{
	t_tuple	result;

	if (is_equal(a.w + b.w, 2.0))
	{
		ft_dprintf(2, "Error: Cannot add two points together.\n");
		exit(1); // or handle error differently
	}

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
	return (result);
}

t_tuple	sub_tuples(t_tuple a, t_tuple b)
{
	t_tuple	result;

	if (is_equal(a.w - b.w, -1.0))
	{
		ft_dprintf(2, "Error: Cannot subtract a point from a vector.\n");
		exit(1);
	}

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
	return (result);
}

t_tuple	negate_tuple(t_tuple a)
{
	t_tuple	result;

	result.x = -a.x;
	result.y = -a.y;
	result.z = -a.z;
	result.w = a.w; // apparently w can be negated but i digress
	return (result);
}