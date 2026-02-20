/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 21:38:20 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/18 20:59:20 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Creates a vector tuple, where w is set to 0 to indicate
// it's a vector, not a point.
float	dot_product(t_tuple a, t_tuple b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

// Calculates the cross product of two vectors, 
// returning a new vector that is perpendicular to both.
t_tuple	cross_product(t_tuple a, t_tuple b)
{
	return (create_vector(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}
