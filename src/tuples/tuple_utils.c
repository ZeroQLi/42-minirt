/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:09:38 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/18 04:27:46 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Creates a tuple with the given x, y, z, w values.
t_tuple	create_tuple(float x, float y, float z, float w)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = w;
	return (tuple);
}

// Creates a point tuple, where w is set to 1 to indicate
// it's a point, not a vector.
t_tuple	create_point(float x, float y, float z)
{
	return (create_tuple(x, y, z, 1.0f));
}

// Creates a vector tuple, where w is set to 0 to indicate
// it's a vector, not a point.
t_tuple	create_vector(float x, float y, float z)
{
	return (create_tuple(x, y, z, 0.0f));
}

// Creates a color tuple, where r, g, b are stored in x, y, z and w is unused.
t_color	create_color(float r, float g, float b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}
