/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:14:16 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/24 01:49:58 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Adds two colors together, component-wise, and returns the resulting color.
t_color	add_colors(t_color a, t_color b)
{
	t_color	result;

	result.r = a.r + b.r;
	result.g = a.g + b.g;
	result.b = a.b + b.b;
	return (result);
}

// Subtracts the second color from the first, component-wise,
// and returns the resulting color.
t_color	sub_colors(t_color a, t_color b)
{
	t_color	result;

	result.r = a.r - b.r;
	result.g = a.g - b.g;
	result.b = a.b - b.b;
	return (result);
}

// Multiplies each component of the color by a scalar value,
// effectively scaling the brightness of the color.
t_color	multiply_colors(t_color a, float num)
{
	t_color	result;

	result.r = a.r * num;
	result.g = a.g * num;
	result.b = a.b * num;
	return (result);
}

// Performs a component-wise multiplication of two colors.
t_color	hadamard_product(t_color a, t_color b)
{
	t_color	result;

	result.r = a.r * b.r;
	result.g = a.g * b.g;
	result.b = a.b * b.b;
	return (result);
}
