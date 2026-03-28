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

t_intersection_list	*intersect_plane(t_ray ray, t_plane *plane)
{
	ray = transform_ray(ray, plane->tf.inv_transform);
	if (fabsf(ray.dir.y) < EPSILON)
		return (intersect_list(intersect(0, NULL, 0), intersect(0, NULL, 0)));
	return (intersect_list(intersect(-ray.origin.y / ray.dir.y, plane, PLANE),
			intersect(0, NULL, 0)));
}
