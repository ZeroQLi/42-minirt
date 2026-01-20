/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:09:38 by mtangalv          #+#    #+#             */
/*   Updated: 2026/01/20 21:54:51 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_tuple	create_tuple(float x, float y, float z, float w)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = w;
	return (tuple);
}

t_tuple	create_point(float x, float y, float z)
{
	return (create_tuple(x, y, z, 1.0f));
}

t_tuple	create_vector(float x, float y, float z)
{
	return (create_tuple(x, y, z, 0.0f));
}

int	is_equal(float a, float b)
{
	return (fabsf(a - b) < EPSILON);
}

int	is_point(t_tuple tuple)
{
	return (is_equal(tuple.w, 1.0f));
}
