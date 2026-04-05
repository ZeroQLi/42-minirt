/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_shadow_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:25:45 by nanasser          #+#    #+#             */
/*   Updated: 2026/04/05 17:25:45 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

bool	shadow_hit_plane(t_ray ray, t_plane *plane, float max_t)
{
	float	t;

	ray = transform_ray(ray, plane->tf.inv_transform);
	if (fabsf(ray.dir.y) < EPSILON)
		return (false);
	t = -ray.origin.y / ray.dir.y;
	return (t >= EPSILON && t < max_t);
}
