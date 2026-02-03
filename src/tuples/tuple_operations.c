/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:09:32 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/03 23:27:52 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	is_equal(float a, float b)
{
	return (fabsf(a - b) < EPSILON);
}

int	is_point(t_tuple tuple)
{
	return (is_equal(tuple.w, 1.0f));
}

t_tuple	add_tuples(t_tuple a, t_tuple b)
{
	t_tuple	result;

	if (is_equal(a.w + b.w, 2.0))
	{
		ft_dprintf(2, "Error: Cannot add two points together.\n");
		exit(1); // or handle error differently (REMOVE/CHANGE LATER)
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
