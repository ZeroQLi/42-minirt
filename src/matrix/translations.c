/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:55:18 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/23 23:56:33 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
// Creates a translation matrix that moves points by (x, y, z).
t_matrix4	translation(float x, float y, float z)
{
	t_matrix4	res;

	res = create_identity();
	res.data[0][3] = x;
	res.data[1][3] = y;
	res.data[2][3] = z;
	return (res);
}

// Creates a scaling matrix that scales points by (x, y, z).
t_matrix4	scaling(float x, float y, float z)
{
	t_matrix4	res;

	res = create_identity();
	res.data[0][0] = x;
	res.data[1][1] = y;
	res.data[2][2] = z;
	return (res);
}

// Creates a rotation matrix that rotates points around the X-axis
// by the given angle in radians.
t_matrix4	rotation_x(float rad)
{
	t_matrix4	res;

	res = create_identity();
	res.data[1][1] = cosf(rad);
	res.data[1][2] = -sinf(rad);
	res.data[2][1] = sinf(rad);
	res.data[2][2] = cosf(rad);
	return (res);
}

// Creates a rotation matrix that rotates points around the Y-axis
// by the given angle in radians.
t_matrix4	rotation_y(float rad)
{
	t_matrix4	res;

	res = create_identity();
	res.data[0][0] = cosf(rad);
	res.data[0][2] = sinf(rad);
	res.data[2][0] = -sinf(rad);
	res.data[2][2] = cosf(rad);
	return (res);
}

// Creates a rotation matrix that rotates points around the Z-axis
// by the given angle in radians.
t_matrix4	rotation_z(float rad)
{
	t_matrix4	res;

	res = create_identity();
	res.data[0][0] = cosf(rad);
	res.data[0][1] = -sinf(rad);
	res.data[1][0] = sinf(rad);
	res.data[1][1] = cosf(rad);
	return (res);
}
