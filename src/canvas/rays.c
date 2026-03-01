/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:30:49 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/01 06:30:00 by nanasser         ###   ########.fr       */
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

t_tuple	position(t_ray ray, float t)
{
	t_tuple	scaled_dir;

	scaled_dir = scalar_multiply(ray.dir, t);
	return (add_tuples(ray.origin, scaled_dir));
}

// Intersects a ray with a sphere, returns the intersection points (t values).
float	*intersect_sphere(t_ray ray, t_sphere *sphere)
{
	t_tuple	sphere_to_ray;
	float	a;
	float	b;
	float	disc;
	float	*intersections;

	(void)sphere; // placeholder
	intersections = ft_calloc(3, sizeof(float));
	if (!intersections)
		return (NULL);
	sphere_to_ray = sub_tuples(ray.origin, create_point(0, 0, 0));
	a = dot_product(ray.dir, ray.dir);
	b = 2 * dot_product(ray.dir, sphere_to_ray);
	disc = (b * b) - (4 * a * (dot_product(sphere_to_ray, sphere_to_ray) - 1));
	if (disc < 0)
		intersections[0] = 0;
	else
	{
		intersections[0] = 2;
		intersections[1] = (-b - sqrtf(disc)) / (2 * a);
		intersections[2] = (-b + sqrtf(disc)) / (2 * a);
	}
	return (intersections);
}

t_intersection	intersect(float t, t_sphere *sphere)
{
	t_intersection	i;

	i.t = t;
	i.object = sphere;
	return (i);
}

t_intersection	*intersection_list(t_intersection i1, t_intersection i2)
{
	t_intersection	*xs;

	xs = ft_calloc(2, sizeof(t_intersection));
	if (!xs)
		return (NULL);
	xs->t = 2;
	xs[0] = i1;
	xs[1] = i2;
	return (xs);
}
