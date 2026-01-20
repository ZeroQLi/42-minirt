/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:36:02 by mtangalv          #+#    #+#             */
/*   Updated: 2026/01/20 21:57:04 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_tuple	scalar_multiply(t_tuple a, float num)
{
	t_tuple	result;
	
	result.x = a.x * num;
	result.y = a.y * num;
	result.z = a.z * num;
	result.w = a.w * num; // apparently w is just modifiable but i digress
	return (result);
}

t_tuple scalar_divide(t_tuple a, float num)
{
	t_tuple result;

	if (fabsf(num) < EPSILON)
	{
		ft_dprintf(2, "Error: Division by zero\n");
		exit(1);
	}
	result.x = a.x / num;
	result.y = a.y / num;
	result.z = a.z / num;
	result.w = a.w / num; // apparently w is just bmodifiable ut i digress
	return (result);
}

float	scalar_magnitude(t_tuple a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w));
}

t_tuple	scalar_normalize(t_tuple a)
{
	float	mag;
	t_tuple	result;

	mag = scalar_magnitude(a);
	if (fabsf(mag) < EPSILON)
	{
		ft_dprintf(2, "Error: Cannot normalize zero vector\n");
		exit(1);
	}
	result.x = a.x / mag;
	result.y = a.y / mag;
	result.z = a.z / mag;
	result.w = a.w / mag; // apparently w is just modifiable but i digress
	return (result);
}