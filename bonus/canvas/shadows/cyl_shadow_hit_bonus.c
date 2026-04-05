/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_shadow_hit_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:26:43 by nanasser          #+#    #+#             */
/*   Updated: 2026/04/05 17:26:43 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

static inline bool	check_caps(t_ray ray, float t)
{
	float	x;
	float	z;

	x = ray.origin.x + t * ray.dir.x;
	z = ray.origin.z + t * ray.dir.z;
	return (((x * x) + (z * z)) <= 1.0f);
}

static bool	cylinder_side_shadow_hit(t_ray ray, t_cylinder *cylinder,
	float quad[3], float max_t)
{
	float	t;
	float	y;

	if (quad[2] < 0)
		return (false);
	t = (-quad[1] - sqrtf(quad[2])) / (2.f * quad[0]);
	y = ray.origin.y + t * ray.dir.y;
	if (t >= EPSILON && t < max_t
		&& y >= -cylinder->height && y <= cylinder->height)
		return (true);
	t = (-quad[1] + sqrtf(quad[2])) / (2.f * quad[0]);
	y = ray.origin.y + t * ray.dir.y;
	if (t >= EPSILON && t < max_t
		&& y >= -cylinder->height && y <= cylinder->height)
		return (true);
	return (false);
}

bool	shadow_hit_cylinder_bonus(t_ray ray, t_cylinder *cylinder, float max_t)
{
	t_tuple	cylinder_to_ray;
	float	quad[3];
	float	t;

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
		if (cylinder_side_shadow_hit(ray, cylinder, quad, max_t))
			return (true);
	}
	if (cylinder->closed == NO || fabsf(ray.dir.y) < EPSILON)
		return (false);
	t = (-cylinder->height - ray.origin.y) / ray.dir.y;
	if (t >= EPSILON && t < max_t && check_caps(ray, t))
		return (true);
	t = (cylinder->height - ray.origin.y) / ray.dir.y;
	return (t >= EPSILON && t < max_t && check_caps(ray, t));
}
