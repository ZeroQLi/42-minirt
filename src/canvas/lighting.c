/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:25:26 by mtangalv          #+#    #+#             */
/*   Updated: 2026/04/05 22:36:54 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	color_from_rgb(int r, int g, int b)
{
	return (create_color(r / 255.0f, g / 255.0f, b / 255.0f));
}

static inline void	compute_diffuse(t_lighting *lighting, t_color color)
{
	lighting->diffuse = multiply_colors(color, lighting->material.diffuse
			* lighting->l_dot_n);
	lighting->specular = create_color(0, 0, 0);
}

t_point_light	point_light(t_tuple position, t_color intensity)
{
	t_point_light	light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}

t_material	create_material(int cr, int cg, int cb)
{
	t_material	material;

	material.color = color_from_rgb(cr, cg, cb);
	material.ambient = 0.5f;
	material.diffuse = 0.9f;
	material.specular = 0.9f;
	material.shininess = 200.0f;
	return (material);
}

// Calculates the color at a point on a surface using the Phong lighting model.
t_color	lighting(t_lighting *lighting, t_ambient *amb)
{
	t_color	color;
	float	l_dot_n;

	color = hadamard_product(lighting->material.color,
			create_color(1, 1, 1));
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
