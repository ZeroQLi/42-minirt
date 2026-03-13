/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:25:26 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/13 09:03:44 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	compute_diffuse(t_light *lighting, t_color color)
{
	float	factor;
	t_tuple	halfv;

	lighting->diffuse = multiply_colors(color, lighting->material.diffuse
			* lighting->l_dot_n);
	// lighting->reflectv = reflect(negate_tuple(lighting->lightv),
	// 		lighting->normalv);
	halfv = scalar_normalize(add_tuples(lighting->lightv, lighting->eyev));
	lighting->r_dot_e = dot_product(lighting->normalv, halfv);
	if (lighting->r_dot_e <= 0)
		lighting->specular = create_color(0, 0, 0);
	else
	{
		factor = powf(lighting->r_dot_e, lighting->material.shininess);
		lighting->specular = multiply_colors(lighting->intensity,
				lighting->material.specular * factor);
	}
}

// t_point_light	point_light(t_tuple position, t_color intensity)
// {
// 	t_point_light	light;

// 	light.position = position;
// 	light.intensity = intensity;
// 	return (light);
// }

t_material	create_material(t_sphere *sp)
{
	t_material	material;

	material.color = color_from_rgb(sp->cr, sp->cg, sp->cb);
	material.ambient = 0.1f;
	material.diffuse = 0.9f;
	material.specular = 0.9f;
	material.shininess = 200.0f;
	return (material);
}

t_color	lighting(t_light *lighting)
{
	t_color	color; // effective_color
	float	l_dot_n; // light dot normal

	color = hadamard_product(lighting->material.color, lighting->intensity);
	lighting->lightv = scalar_normalize(sub_tuples(lighting->position,
				lighting->h_position));
	lighting->ambient = multiply_colors(color, lighting->material.ambient);
	l_dot_n = dot_product(lighting->lightv, lighting->normalv);
	lighting->l_dot_n = l_dot_n;
	if (l_dot_n < 0)
	{
		lighting->diffuse = create_color(0, 0, 0);
		lighting->specular = create_color(0, 0, 0);
	}
	else
		compute_diffuse(lighting, color);
	lighting->result = add_colors(add_colors(lighting->ambient,
				lighting->diffuse), lighting->specular);
	return (lighting->result);
}
