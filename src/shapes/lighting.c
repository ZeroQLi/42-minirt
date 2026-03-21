/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:25:26 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/21 18:36:42 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	compute_diffuse(t_lighting *lighting, t_color color)
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
		lighting->specular = multiply_colors(lighting->p_light.intensity,
				lighting->material.specular * factor);
	}
}

t_point_light	point_light(t_tuple position, t_color intensity)
{
	t_point_light	light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}

t_material	create_material(int cr, int cg, int cb, float al_ratio)
{
	t_material	material;

	// material.color = create_color(1, 1, 1);
	material.color = color_from_rgb(cr, cg, cb);
	material.ambient = al_ratio;
	material.diffuse = 0.9f;
	material.specular = 0.9f;
	material.shininess = 200.0f;
	return (material);
}

t_color	lighting(t_lighting *lighting, t_ambient *amb)
{
	t_color	color; // effective_color
	float	l_dot_n; // light dot normal

	color = hadamard_product(lighting->material.color, lighting->p_light.intensity);
	lighting->lightv = scalar_normalize(sub_tuples(lighting->p_light.position,
				lighting->h_position));
	lighting->ambient = ambient_from_world(*lighting, amb);
	l_dot_n = dot_product(lighting->lightv, lighting->normalv);
	lighting->l_dot_n = l_dot_n;
	if (l_dot_n < 0 || lighting->in_shadow == YES)
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
