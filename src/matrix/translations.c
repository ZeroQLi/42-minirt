/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:55:18 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/05 17:12:49 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_matrix4	translation(float x, float y, float z)
{
	t_matrix4	res;

	res = create_identity();
	res.data[0][3] = x;
	res.data[1][3] = y;
	res.data[2][3] = z;
	return (res);
}

t_matrix4	scaling(float x, float y, float z)
{
	t_matrix4	res;

	res = create_identity();
	res.data[0][0] = x;
	res.data[1][1] = y;
	res.data[2][2] = z;
	return (res);
}

t_matrix4	rotation_x(float rad)
{
	t_matrix4	res;

	res = create_identity();
	res.data[1][1] = cos(rad);
	res.data[1][2] = -sin(rad);
	res.data[2][1] = sin(rad);
	res.data[2][2] = cos(rad);
	return (res);
}

t_matrix4	rotation_y(float rad)
{
	t_matrix4	res;

	res = create_identity();
	res.data[0][0] = cos(rad);
	res.data[0][2] = sin(rad);
	res.data[2][0] = -sin(rad);
	res.data[2][2] = cos(rad);
	return (res);
}

t_matrix4	rotation_z(float rad)
{
	t_matrix4	res;

	res = create_identity();
	res.data[0][0] = cos(rad);
	res.data[0][1] = -sin(rad);
	res.data[1][0] = sin(rad);
	res.data[1][1] = cos(rad);
	return (res);
}
