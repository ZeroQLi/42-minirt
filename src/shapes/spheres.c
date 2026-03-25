/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:49:27 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/25 21:37:14 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	set_transform(t_shape_transform *tf, t_matrix4 transform)
{
	tf->transform = transform;
	tf->inv_transform = invert_4x4(transform);
	tf->transposed_inv = transpose_matrix4(tf->inv_transform);
}
