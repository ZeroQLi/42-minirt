/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:30:49 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/26 17:47:02 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_ray	create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.dir = direction;
	return (ray);
}

t_tuple	position(t_ray ray, float t)
{
	t_tuple	scaled_dir;

	scaled_dir = scalar_multiply(ray.dir, t);
	return (add_tuples(ray.origin, scaled_dir));
}

float	*intersect_sphere(t_ray ray, t_sphere *sphere)
{
	t_tuple	sphere_to_ray;
	float	a;
	float	b;
	float	disc;
	float	*intersections;

	(void) sphere;
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
