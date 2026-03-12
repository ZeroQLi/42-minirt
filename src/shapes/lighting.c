/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:25:26 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/12 17:01:38 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_point_light	point_light(t_tuple position, t_color intensity)
{
	t_point_light	light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}

t_material	create_material(void)
{
	t_material	material;

	material.color = create_color(1, 1, 1);
	material.ambient = 0.1f;
	material.diffuse = 0.9f;
	material.specular = 0.9f;
	material.shininess = 200.0f;
	return (material);
}

void	lighting(t_lighting lighting)
{
	(void) lighting;
	return ;
}