/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 21:07:25 by nanasser          #+#    #+#             */
/*   Updated: 2026/03/27 21:07:25 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

bool	intersect_plane(t_intersection_list *acc, t_ray ray,
	t_plane *plane)
{
	ray = transform_ray(ray, plane->tf.inv_transform);
	if (fabsf(ray.dir.y) < EPSILON)
		return (true);
	return (intersections_push(acc,
			intersect(-ray.origin.y / ray.dir.y, plane, PLANE)));
}
