/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:25:45 by nanasser          #+#    #+#             */
/*   Updated: 2026/03/28 00:25:45 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	init_spheres(t_sphere *sp)
{
	t_matrix4	transform;
	t_sphere	*tmp;

	tmp = sp;
	while (tmp)
	{
		tmp->position = create_point(tmp->px, tmp->py, tmp->pz);
		tmp->material = create_material(tmp->cr, tmp->cg, tmp->cb);
		transform = translation(tmp->position.x, tmp->position.y,
				tmp->position.z);
		transform = matrix_multiply(transform, scaling(tmp->diameter,
					tmp->diameter, tmp->diameter));
		set_transform(&tmp->tf, transform);
		tmp = tmp->next;
	}
}

void	init_planes(t_plane *pl)
{
	t_matrix4	transform;
	t_plane		*tmp;

	tmp = pl;
	while (tmp)
	{
		tmp->position = create_point(tmp->px, tmp->py, tmp->pz);
		tmp->rotation = scalar_normalize(create_vector(tmp->rx, tmp->ry,
					tmp->rz));
		tmp->material = create_material(tmp->cr, tmp->cg, tmp->cb);
		transform = translation(tmp->position.x, tmp->position.y,
				tmp->position.z);
		transform = matrix_multiply(transform,
				align_y_to_vector(tmp->rotation));
		set_transform(&tmp->tf, transform);
		tmp = tmp->next;
	}
}

void	init_cylinders(t_cylinder *cy)
{
	t_matrix4	transform;
	t_cylinder	*tmp;

	tmp = cy;
	while (tmp)
	{
		tmp->position = create_point(tmp->px, tmp->py, tmp->pz);
		tmp->rotation = scalar_normalize(create_vector(tmp->rx, tmp->ry,
					tmp->rz));
		tmp->material = create_material(tmp->cr, tmp->cg, tmp->cb);
		transform = translation(tmp->position.x, tmp->position.y,
				tmp->position.z);
		transform = matrix_multiply(transform,
				align_y_to_vector(tmp->rotation));
		transform = matrix_multiply(transform, scaling(tmp->diameter,
					1.0f, tmp->diameter));
		set_transform(&tmp->tf, transform);
		tmp->closed = YES;
		tmp = tmp->next;
	}
}
