/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:09:32 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/26 18:55:13 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Checks if two floats are equal within a small epsilon range.
int	is_equal(float a, float b)
{
	return (fabsf(a - b) < EPSILON);
}

// Checks if a tuple is a point (w = 1.0) or a vector (w = 0.0).
int	is_point(t_tuple tuple)
{
	return (is_equal(tuple.w, 1.0f));
}

// Adding two tuples is not defined if both are points (w = 1), 
// but it is defined if one or both are vectors (w = 0).
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

// Subtracts one tuple from another.
t_tuple	sub_tuples(t_tuple a, t_tuple b)
{
	t_tuple	result;

	if (is_equal(a.w - b.w, -1.0))
	{
		ft_dprintf(2, "Error: Cannot subtract a point from a vector.\n");
		exit(1); // REMOVE/CHANGE LATER
	}
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
	return (result);
}

// Negating a tuple negates its x, y, and z components but leaves w unchanged.
t_tuple	negate_tuple(t_tuple a)
{
	t_tuple	result;

	result.x = -a.x;
	result.y = -a.y;
	result.z = -a.z;
	result.w = -a.w;
	return (result);
}
