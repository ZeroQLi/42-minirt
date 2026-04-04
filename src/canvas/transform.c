/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:49:27 by mtangalv          #+#    #+#             */
/*   Updated: 2026/04/04 15:07:49 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_matrix4	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward;
	t_tuple		up_normalized;
	t_tuple		left;
	t_tuple		true_up;
	t_matrix4	orientation;

	forward = scalar_normalize(sub_tuples(to, from));
	up_normalized = scalar_normalize(up);
	if (fabsf(dot_product(forward, up_normalized)) > 0.999f)
	{
		if (fabsf(forward.z) < 0.999f)
			up_normalized = create_vector(0, 0, 1);
		else
			up_normalized = create_vector(1, 0, 0);
	}
	left = scalar_normalize(cross_product(forward, up_normalized));
	true_up = cross_product(left, forward);
	true_up = scalar_normalize(true_up);
	orientation = (t_matrix4){.data = {
	{left.x, left.y, left.z, 0},
	{true_up.x, true_up.y, true_up.z, 0},
	{-forward.x, -forward.y, -forward.z, 0}, {0, 0, 0, 1}}};
	return (matrix_multiply(orientation,
			translation(-from.x, -from.y, -from.z)));
}

void	set_transform(t_shape_transform *tf, t_matrix4 transform)
{
	tf->transform = transform;
	tf->inv_transform = invert_4x4(transform);
	tf->transposed_inv = transpose_matrix4(tf->inv_transform);
}
