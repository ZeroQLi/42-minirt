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

static inline float	check_caps(t_ray ray, float t)
{
	float	x;
	float	z;

	x = ray.origin.x + t * ray.dir.x;
	z = ray.origin.z + t * ray.dir.z;
	return (((x * x) + (z * z)) <= 1.0f);
}

static inline t_intersection_list	*intersect_caps(t_cylinder *cyl, t_ray ray,
			t_intersection_list *xs)
{
	float			t;
	t_intersection	i1;
	t_intersection	i2;

	i1 = intersect(0, NULL, 0);
	i2 = intersect(0, NULL, 0);
	if (fabsf(ray.dir.y) < EPSILON)
		return (xs);
	t = (-cyl->height - ray.origin.y) / ray.dir.y;
	if (check_caps(ray, t))
		i1 = intersect(t, cyl, CYLINDER);
	t = (cyl->height - ray.origin.y) / ray.dir.y;
	if (check_caps(ray, t))
		i2 = intersect(t, cyl, CYLINDER);
	return (intersections_joined(xs, intersect_list(i1, i2)));
}

static inline t_intersection_list	*intersect_cylinder_height(t_ray ray,
		float *intersections, t_cylinder *cylinder)
{
	float	y0;
	float	y1;
	void	*obj1;
	void	*obj2;

	y0 = ray.origin.y + intersections[1] * ray.dir.y;
	y1 = ray.origin.y + intersections[2] * ray.dir.y;
	obj1 = NULL;
	if (y0 >= -cylinder->height && y0 <= cylinder->height)
		obj1 = cylinder;
	obj2 = NULL;
	if (y1 >= -cylinder->height && y1 <= cylinder->height)
		obj2 = cylinder;
	if (cylinder->closed == YES)
		return (intersect_caps(cylinder, ray,
				intersect_list(intersect(intersections[1], obj1, CYLINDER),
					intersect(intersections[2], obj2, CYLINDER))));
	return (intersect_list(intersect(intersections[1], obj1, CYLINDER),
			intersect(intersections[2], obj2, CYLINDER)));
}

static inline t_intersection_list	*intersect_cylinder_caps_only(t_ray ray,
		t_cylinder *cylinder)
{
	t_intersection_list	*empty_xs;

	empty_xs = intersect_list(intersect(0, NULL, 0), intersect(0, NULL, 0));
	if (cylinder->closed == YES)
		return (intersect_caps(cylinder, ray, empty_xs));
	return (empty_xs);
}

t_intersection_list	*intersect_cylinder(t_ray ray, t_cylinder *cylinder)
{
	t_tuple			cylinder_to_ray;
	float			a;
	float			b;
	float			disc;
	float			intersections[3];

	ray = transform_ray(ray, cylinder->tf.inv_transform);
	cylinder_to_ray = sub_tuples(ray.origin, create_point(0, 0, 0));
	a = (ray.dir.x * ray.dir.x) + (ray.dir.z * ray.dir.z);
	if (fabsf(a) < EPSILON)
		return (intersect_cylinder_caps_only(ray, cylinder));
	b = 2.f * ((ray.dir.x * cylinder_to_ray.x)
			+ (ray.dir.z * cylinder_to_ray.z));
	disc = (b * b) - (4.f * a * ((cylinder_to_ray.x * cylinder_to_ray.x)
				+ (cylinder_to_ray.z * cylinder_to_ray.z) - 1.f));
	if (disc < 0)
		return (intersect_cylinder_caps_only(ray, cylinder));
	intersections[0] = 2;
	intersections[1] = (-b - sqrtf(disc)) / (2.f * a);
	intersections[2] = (-b + sqrtf(disc)) / (2.f * a);
	return (intersect_cylinder_height(ray, intersections, cylinder));
}
