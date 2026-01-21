/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:14:16 by mtangalv          #+#    #+#             */
/*   Updated: 2026/01/21 13:36:19 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color add_colors(t_color a, t_color b)
{
	t_color result;

	result.r = a.r + b.r;
	result.g = a.g + b.g;
	result.b = a.b + b.b;
	return (result);
}

t_color sub_colors(t_color a, t_color b)
{
	t_color result;

	result.r = a.r - b.r;
	result.g = a.g - b.g;
	result.b = a.b - b.b;
	return (result);
}

t_color multiply_colors(t_color a, float num)
{
	t_color result;

	result.r = a.r * num;
	result.g = a.g * num;
	result.b = a.b * num;
	return (result);
}

t_color hadamard_product(t_color a, t_color b)
{
	t_color result;

	result.r = a.r * b.r;
	result.g = a.g * b.g;
	result.b = a.b * b.b;
	return (result);
}