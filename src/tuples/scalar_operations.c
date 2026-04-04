/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:36:02 by mtangalv          #+#    #+#             */
/*   Updated: 2026/04/04 14:50:20 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Multiplies a tuple by a scalar value, scaling its components.
t_tuple	scalar_multiply(t_tuple a, float num)
{
	t_tuple	result;

	result.x = a.x * num;
	result.y = a.y * num;
	result.z = a.z * num;
	result.w = a.w * num;
	return (result);
}

// Divides a tuple by a scalar value, scaling its components down.
t_tuple	scalar_divide(t_tuple a, float num)
{
	t_tuple	result;

	if (fabsf(num) < EPSILON)
	{
		error_msg(YES, "Division by zero", 2);
		return (create_vector(0, 0, 0));
	}
	result.x = a.x / num;
	result.y = a.y / num;
	result.z = a.z / num;
	result.w = a.w / num;
	return (result);
}

// Calculates the magnitude (length) of a tuple, treating it as a vector.
float	scalar_magnitude(t_tuple a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w));
}

// Normalizes a tuple, returning a unit vector in the same direction.
t_tuple	scalar_normalize(t_tuple a)
{
	float	mag;
	t_tuple	result;

	mag = scalar_magnitude(a);
	if (fabsf(mag) < EPSILON)
	{
		error_msg(NO, "Cannot normalize zero vector", 2);
		return (create_vector(0, 0, 0));
	}
	result.x = a.x / mag;
	result.y = a.y / mag;
	result.z = a.z / mag;
	result.w = a.w / mag;
	return (result);
}
