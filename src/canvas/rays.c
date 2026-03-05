/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:30:49 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/05 05:21:02 by nanasser         ###   ########.fr       */
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

// Intersects a ray with a sphere, returns the intersection points (t values).
t_intersection_list	*intersect_sphere(t_ray ray, t_sphere *sphere)
{
	t_tuple				sphere_to_ray; // REMOVE/CHANGE LATER
	float				a;
	float				b;
	float				disc;
	float				intersections[3];

	sphere_to_ray = sub_tuples(ray.origin, create_point(0, 0, 0));
	a = dot_product(ray.dir, ray.dir);
	b = 2 * dot_product(ray.dir, sphere_to_ray);
	disc = (b * b) - (4 * a * (dot_product(sphere_to_ray, sphere_to_ray) - 1));
	if (disc < 0)
		return (intersection_list(intersect(0, NULL), intersect(0, NULL)));
	else
	{
		intersections[0] = 2;
		intersections[1] = (-b - sqrtf(disc)) / (2 * a);
		intersections[2] = (-b + sqrtf(disc)) / (2 * a);
	}
	return (intersection_list(intersect(intersections[1], sphere),
			intersect(intersections[2], sphere)));
}

// Creates an intersection object with the given t value and sphere reference.
t_intersection	intersect(float t, t_sphere *sphere)
{
	t_intersection	i;

	i.t = t;
	i.object = sphere;
	return (i);
}

t_intersection	hit(t_intersection_list *xs)
{
	int	i;
	int	hit_index;

	hit_index = -1;
	i = 0;
	while (i < xs->count)
	{
		if (xs->items[i].t >= 0 && (hit_index == -1 || xs->items[i].t < xs->items[hit_index].t))
			hit_index = i;
		i++;
	}
	if (hit_index == -1)
		return (intersect(0, NULL));
	return (xs->items[hit_index]);
}

// Creates an intersection list containing two intersections.
t_intersection_list	*intersection_list(t_intersection i1, t_intersection i2)
{
	t_intersection_list	*xs;

	xs = ft_calloc(1, sizeof(t_intersection_list));
	if (!xs)
		return (NULL);
	xs->items = ft_calloc(3, sizeof(t_intersection));
	if (!xs->items)
	{
		free(xs);
		return (NULL);
	}
	if (i1.t == 0 && i2.t == 0)
		xs->count = 0;
	else
		xs->count = 2;
	xs->items[0] = i1;
	xs->items[1] = i2;
	return (xs);
}
