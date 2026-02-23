/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:36:02 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/24 01:50:00 by nanasser         ###   ########.fr       */
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
	result.w = a.w * num; // apparently w is just modifiable but i digress
	return (result);
}

// Divides a tuple by a scalar value, scaling its components down.
t_tuple	scalar_divide(t_tuple a, float num)
{
	t_tuple	result;

	if (fabsf(num) < EPSILON)
	{
		ft_dprintf(2, "Error: Division by zero\n");
		exit(1);
	}
	result.x = a.x / num;
	result.y = a.y / num;
	result.z = a.z / num;
	result.w = a.w / num; // apparently w is just bmodifiable but i digress
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
		ft_dprintf(2, "Error: Cannot normalize zero vector\n");
		exit(1); // REMOVE/CHANGE LATER
	}
	result.x = a.x / mag;
	result.y = a.y / mag;
	result.z = a.z / mag;
	result.w = a.w / mag; // apparently w is just modifiable but i digress
	return (result);
}
