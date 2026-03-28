/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:49:27 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/28 17:27:27 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_matrix4	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward;
	t_tuple		left;
	t_tuple		true_up;
	t_matrix4	orientation;

	forward = scalar_normalize(sub_tuples(to, from));
	left = cross_product(forward, scalar_normalize(up));
	true_up = cross_product(left, forward);
	orientation = (t_matrix4){.data = {
	{left.x, left.y, left.z, 0},
	{true_up.x, true_up.y, true_up.z, 0},
	{-forward.x, -forward.y, -forward.z, 0},
	{0, 0, 0, 1}
	}};
	return (matrix_multiply(orientation,
			translation(-from.x, -from.y, -from.z)));
}

void	set_transform(t_shape_transform *tf, t_matrix4 transform)
{
	tf->transform = transform;
	tf->inv_transform = invert_4x4(transform);
	tf->transposed_inv = transpose_matrix4(tf->inv_transform);
}
