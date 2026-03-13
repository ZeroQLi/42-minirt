/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:17:13 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/13 08:57:47 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_tuple	normal_at(t_sphere *sphere, t_tuple world_point)
{
	t_tuple		object_point;
	t_tuple		object_normal;
	t_tuple		w_normal;
	t_matrix4	inv_transform;
	t_matrix4	transposed_inv;

	inv_transform = sphere->inv_transform;
	object_point = matrix4_tuple_multiply(inv_transform, world_point);
	object_normal = sub_tuples(object_point, create_point(0, 0, 0));
	transposed_inv = transpose_matrix4(inv_transform);
	w_normal = matrix4_tuple_multiply(transposed_inv, object_normal);
	w_normal = create_vector(w_normal.x, w_normal.y, w_normal.z);
	return (scalar_normalize(w_normal));
}

// given a vector "in" and a vector "normal", return its reflection
// * follows the formula: in - normal * 2 * dot(in, normal)
t_tuple	reflect(t_tuple in, t_tuple normal)
{
	t_tuple	reflection;
	float	dot;

	dot = dot_product(in, normal) * 2;
	reflection = sub_tuples(in, scalar_multiply(normal, dot));
	return (reflection);
}
