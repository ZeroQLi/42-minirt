/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:09:38 by mtangalv          #+#    #+#             */
/*   Updated: 2026/01/18 23:34:26 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_tuple	create_point(double x, double y, double z)
{
	t_tuple	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.w = 1.0; // w = 1 for points
	return (point);
}

t_tuple	create_vector(double x, double y, double z)
{
	t_tuple	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = 0.0; // w = 0 for vectors
	return (vector);
}

int	is_point(t_tuple tuple)
{
	return (tuple.w == 1.0);
}

int	is_equal(float a, float b)
{
	return (fabs(a - b) < EPSILON);
}
