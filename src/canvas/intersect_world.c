/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 16:33:47 by nanasser          #+#    #+#             */
/*   Updated: 2026/03/28 16:33:47 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool	add_sphere_intersections(t_intersection_list *acc, t_ray ray,
	t_sphere *sphere)
{
	t_tuple	sphere_to_ray;
	float	a;
	float	b;
	float	disc;

	ray = transform_ray(ray, sphere->tf.inv_transform);
	sphere_to_ray = sub_tuples(ray.origin, create_point(0, 0, 0));
	a = dot_product(ray.dir, ray.dir);
	b = 2.f * dot_product(ray.dir, sphere_to_ray);
	disc = (b * b) - (4.f * a
			* (dot_product(sphere_to_ray, sphere_to_ray) - 1.f));
	if (disc < 0)
		return (true);
	if (!intersections_push(acc,
			intersect((-b - sqrtf(disc)) / (2.f * a), sphere, SPHERE)))
		return (false);
	if (!intersections_push(acc,
			intersect((-b + sqrtf(disc)) / (2.f * a), sphere, SPHERE)))
		return (false);
	return (true);
}

static bool	add_plane_intersections(t_intersection_list *acc, t_ray ray,
	t_plane *plane)
{
	ray = transform_ray(ray, plane->tf.inv_transform);
	if (fabsf(ray.dir.y) < EPSILON)
		return (true);
	return (intersections_push(acc,
			intersect(-ray.origin.y / ray.dir.y, plane, PLANE)));
}

static inline bool	check_caps(t_ray ray, float t)
{
	float	x;
	float	z;

	x = ray.origin.x + t * ray.dir.x;
	z = ray.origin.z + t * ray.dir.z;
	return (((x * x) + (z * z)) <= 1.0f);
}

static bool	add_cylinder_caps(t_intersection_list *acc, t_ray ray,
	t_cylinder *cylinder)
{
	float	t;

	if (cylinder->closed == NO || fabsf(ray.dir.y) < EPSILON)
		return (true);
	t = (-cylinder->height - ray.origin.y) / ray.dir.y;
	if (check_caps(ray, t) && !intersections_push(acc,
				intersect(t, cylinder, CYLINDER)))
		return (false);
	t = (cylinder->height - ray.origin.y) / ray.dir.y;
	if (check_caps(ray, t) && !intersections_push(acc,
				intersect(t, cylinder, CYLINDER)))
		return (false);
	return (true);
}

static bool	add_cylinder_intersections(t_intersection_list *acc, t_ray ray,
	t_cylinder *cylinder)


{
	t_tuple	cylinder_to_ray;
	float	a;
	float	b;
	float	disc;
	float	t;
	float	y;

	ray = transform_ray(ray, cylinder->tf.inv_transform);
	a = (ray.dir.x * ray.dir.x) + (ray.dir.z * ray.dir.z);
	if (fabsf(a) >= EPSILON)
	{
		cylinder_to_ray = sub_tuples(ray.origin, create_point(0, 0, 0));
		b = 2.f * ((ray.dir.x * cylinder_to_ray.x)
				+ (ray.dir.z * cylinder_to_ray.z));
		disc = (b * b) - (4.f * a * ((cylinder_to_ray.x * cylinder_to_ray.x)
					+ (cylinder_to_ray.z * cylinder_to_ray.z) - 1.f));
		if (disc >= 0)
		{
			t = (-b - sqrtf(disc)) / (2.f * a);
			y = ray.origin.y + t * ray.dir.y;
			if (y >= -cylinder->height && y <= cylinder->height
				&& !intersections_push(acc, intersect(t, cylinder, CYLINDER)))
				return (false);
			t = (-b + sqrtf(disc)) / (2.f * a);
			y = ray.origin.y + t * ray.dir.y;
			if (y >= -cylinder->height && y <= cylinder->height
				&& !intersections_push(acc, intersect(t, cylinder, CYLINDER)))
				return (false);
		}
	}
	return (add_cylinder_caps(acc, ray, cylinder));
}

t_intersection_list	*intersect_world(t_world *w, t_ray r)
{
	t_intersection_list	*acc;
	t_sphere			*sp;
	t_plane				*pl;
	t_cylinder			*cy;

	acc = create_intersections();
	if (!acc)
		return (NULL);
	sp = w->sp;
	while (sp)
	{
		if (!add_sphere_intersections(acc, r, sp))
			return (free_intersections(acc), NULL);
		sp = sp->next;
	}
	pl = w->pl;
	while (pl)
	{
		if (!add_plane_intersections(acc, r, pl))
			return (free_intersections(acc), NULL);
		pl = pl->next;
	}
	cy = w->cy;
	while (cy)
	{
		if (!add_cylinder_intersections(acc, r, cy))
			return (free_intersections(acc), NULL);
		cy = cy->next;
	}
	return (acc);
}
