/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 21:07:28 by nanasser          #+#    #+#             */
/*   Updated: 2026/03/27 21:07:28 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

// Intersects a ray with a sphere, returns the intersection points (t values).
t_intersection_list	*intersect_sphere(t_ray ray, t_sphere *sphere)
{
	t_tuple				sphere_to_ray;
	float				a;
	float				b;
	float				disc;
	float				intersections[3];

	ray = transform_ray(ray, sphere->tf.inv_transform);
	sphere_to_ray = sub_tuples(ray.origin, create_point(0, 0, 0));
	a = dot_product(ray.dir, ray.dir);
	b = 2.f * dot_product(ray.dir, sphere_to_ray);
	disc = (b * b) - (4.f * a
			* (dot_product(sphere_to_ray, sphere_to_ray) - 1.f));
	if (disc < 0)
		return (intersect_list(intersect(0, NULL, 0), intersect(0, NULL, 0)));
	intersections[0] = 2;
	intersections[1] = (-b - sqrtf(disc)) / (2.f * a);
	intersections[2] = (-b + sqrtf(disc)) / (2.f * a);
	return (intersect_list(intersect(intersections[1], sphere, SPHERE),
			intersect(intersections[2], sphere, SPHERE)));
}
