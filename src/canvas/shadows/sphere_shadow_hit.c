/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_shadow_hit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 00:00:00 by nanasser          #+#    #+#             */
/*   Updated: 2026/04/01 00:00:00 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

bool	shadow_hit_sphere(t_ray ray, t_sphere *sphere, float max_t)
{
	t_tuple	sphere_to_ray;
	float	a;
	float	b;
	float	disc;
	float	t;

	ray = transform_ray(ray, sphere->tf.inv_transform);
	sphere_to_ray = sub_tuples(ray.origin, create_point(0, 0, 0));
	a = dot_product(ray.dir, ray.dir);
	b = 2.f * dot_product(ray.dir, sphere_to_ray);
	disc = (b * b) - (4.f * a
			* (dot_product(sphere_to_ray, sphere_to_ray) - 1.f));
	if (disc < 0)
		return (false);
	t = (-b - sqrtf(disc)) / (2.f * a);
	if (t >= EPSILON && t < max_t)
		return (true);
	t = (-b + sqrtf(disc)) / (2.f * a);
	return (t >= EPSILON && t < max_t);
}
