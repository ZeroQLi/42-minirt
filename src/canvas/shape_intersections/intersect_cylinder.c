/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 21:07:33 by nanasser          #+#    #+#             */
/*   Updated: 2026/03/27 21:07:33 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

// Checks if the intersection at t is within the radius of the cylinder's caps.
static inline bool	check_caps(t_ray ray, float t)
{
	float	x;
	float	z;

	x = ray.origin.x + t * ray.dir.x;
	z = ray.origin.z + t * ray.dir.z;
	return (((x * x) + (z * z)) <= 1.0f);
}

// Computes the intersections of a ray with the caps of a closed cylinder, if
// the ray is not parallel to the caps.
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

static inline bool	add_cylinder_side_intersections(t_intersection_list *acc,
	t_ray ray, t_cylinder *cylinder, float quad[3])
{
	float	t;
	float	y;

	if (quad[2] < 0)
		return (true);
	t = (-quad[1] - sqrtf(quad[2])) / (2.f * quad[0]);
	y = ray.origin.y + t * ray.dir.y;
	if (y >= -cylinder->height && y <= cylinder->height
		&& !intersections_push(acc, intersect(t, cylinder, CYLINDER)))
		return (false);
	t = (-quad[1] + sqrtf(quad[2])) / (2.f * quad[0]);
	y = ray.origin.y + t * ray.dir.y;
	if (y >= -cylinder->height && y <= cylinder->height
		&& !intersections_push(acc, intersect(t, cylinder, CYLINDER)))
		return (false);
	return (true);
}

// Computes the intersections of a ray with a cylinder, including both the
// curved surface and the caps if the cylinder is closed.
bool	intersect_cylinder(t_intersection_list *acc, t_ray ray,
	t_cylinder *cylinder)
{
	t_tuple	cylinder_to_ray;
	float	quad[3];

	ray = transform_ray(ray, cylinder->tf.inv_transform);
	quad[0] = (ray.dir.x * ray.dir.x) + (ray.dir.z * ray.dir.z);
	if (fabsf(quad[0]) >= EPSILON)
	{
		cylinder_to_ray = sub_tuples(ray.origin, create_point(0, 0, 0));
		quad[1] = 2.f * ((ray.dir.x * cylinder_to_ray.x)
				+ (ray.dir.z * cylinder_to_ray.z));
		quad[2] = (quad[1] * quad[1]) - (4.f * quad[0]
				* ((cylinder_to_ray.x * cylinder_to_ray.x)
					+ (cylinder_to_ray.z * cylinder_to_ray.z) - 1.f));
		if (!add_cylinder_side_intersections(acc, ray, cylinder, quad))
			return (false);
	}
	return (add_cylinder_caps(acc, ray, cylinder));
}
