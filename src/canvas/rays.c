/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:30:49 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/11 18:01:11 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Creates a ray with the given origin and direction,
// while normalizing the direction vector.
t_ray	create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.dir = scalar_normalize(direction);
	return (ray);
}

// Calculates the position along a ray at a given distance t.
t_tuple	position(t_ray ray, float t)
{
	t_tuple	scaled_dir;

	scaled_dir = scalar_multiply(ray.dir, t);
	return (add_tuples(ray.origin, scaled_dir));
}

t_ray	transform_ray(t_ray ray, t_matrix4 matrix)
{
	t_tuple	new_origin;
	t_tuple	new_dir;
	t_ray	new_ray;

	new_origin = matrix4_tuple_multiply(matrix, ray.origin);
	new_dir = matrix4_tuple_multiply(matrix, ray.dir);
	new_ray.origin = new_origin;
	new_ray.dir = new_dir;
	return (new_ray);
}
