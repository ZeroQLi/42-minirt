/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:17:13 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/23 21:12:48 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_tuple	normal_at_cylinder(t_cylinder *cylinder, t_tuple world_point)
{
	t_tuple		object_point;
	t_tuple		object_normal;
	t_tuple		w_normal;
	t_matrix4	inv_transform;
	t_matrix4	transposed_inv;
	float		dist;

	inv_transform = cylinder->tf.inv_transform;
	object_point = matrix4_tuple_multiply(inv_transform, world_point);
	if (cylinder->closed == YES)
	{
		dist = (object_point.x * object_point.x)
			+ (object_point.z * object_point.z);
		if (dist <= 1.0f && object_point.y >= cylinder->height - EPSILON)
			object_normal = create_vector(0, 1, 0);
		else if (dist <= 1.0f && object_point.y <= -cylinder->height + EPSILON)
			object_normal = create_vector(0, -1, 0);
		else
			object_normal = create_vector(object_point.x, 0, object_point.z);
	}
	else
		object_normal = create_vector(object_point.x, 0, object_point.z);
	transposed_inv = transpose_matrix4(inv_transform);
	w_normal = matrix4_tuple_multiply(transposed_inv, object_normal);
	w_normal = create_vector(w_normal.x, w_normal.y, w_normal.z);
	return (scalar_normalize(w_normal));
}

static t_tuple	normal_at_sphere(t_sphere *sphere, t_tuple world_point)
{
	t_tuple		object_point;
	t_tuple		object_normal;
	t_tuple		w_normal;
	t_matrix4	inv_transform;
	t_matrix4	transposed_inv;

	inv_transform = sphere->tf.inv_transform;
	object_point = matrix4_tuple_multiply(inv_transform, world_point);
	object_normal = sub_tuples(object_point, create_point(0, 0, 0));
	transposed_inv = transpose_matrix4(inv_transform);
	w_normal = matrix4_tuple_multiply(transposed_inv, object_normal);
	w_normal = create_vector(w_normal.x, w_normal.y, w_normal.z);
	return (scalar_normalize(w_normal));
}

static t_tuple	normal_at_plane(t_plane *plane, t_tuple world_point)
{
	t_tuple		object_normal;
	t_tuple		w_normal;
	t_matrix4	transposed_inv;

	(void)world_point;
	object_normal = create_vector(0, 1, 0);
	// Transform local plane normal into world space with inverse-transpose.
	transposed_inv = transpose_matrix4(plane->tf.inv_transform);
	w_normal = matrix4_tuple_multiply(transposed_inv, object_normal);
	w_normal = create_vector(w_normal.x, w_normal.y, w_normal.z);
	return (scalar_normalize(w_normal));
}

t_tuple	normal_at(void *object, t_type type, t_tuple world_point)
{
	if (!object)
		return (create_vector(0, 0, 0));
	if (type == SPHERE)
		return (normal_at_sphere((t_sphere *)object, world_point));
	else if (type == PLANE)
		return (normal_at_plane((t_plane *)object, world_point));
	else if (type == CYLINDER)
		return (normal_at_cylinder((t_cylinder *)object, world_point));
	return (create_vector(0, 0, 0));
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
