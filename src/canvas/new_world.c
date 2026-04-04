/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_world.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 21:16:56 by nanasser          #+#    #+#             */
/*   Updated: 2026/03/13 21:16:56 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Computes a rotation matrix that aligns the y-axis to the given vector.
t_matrix4	align_y_to_vector(t_tuple axis)
{
	t_tuple		y_axis;
	t_tuple		x_axis;
	t_tuple		z_axis;
	t_tuple		ref_axis;
	t_matrix4	rot;

	y_axis = scalar_normalize(axis);
	if (fabsf(y_axis.x) > 0.9f)
		ref_axis = create_vector(0, 1, 0);
	else
		ref_axis = create_vector(1, 0, 0);
	x_axis = scalar_normalize(cross_product(ref_axis, y_axis));
	z_axis = cross_product(y_axis, x_axis);
	rot = create_identity();
	rot.data[0][0] = x_axis.x;
	rot.data[1][0] = x_axis.y;
	rot.data[2][0] = x_axis.z;
	rot.data[0][1] = y_axis.x;
	rot.data[1][1] = y_axis.y;
	rot.data[2][1] = y_axis.z;
	rot.data[0][2] = z_axis.x;
	rot.data[1][2] = z_axis.y;
	rot.data[2][2] = z_axis.z;
	return (rot);
}

// Initializes the camera transform and other precomputed values for rendering.
void	camera(t_camera *cam)
{
	float	half_view;
	float	aspect;

	cam->position = create_point(cam->px, cam->py, cam->pz);
	cam->rotation = scalar_normalize(create_vector(cam->rx, cam->ry, cam->rz));
	if (fabsf(cam->rotation.x) < EPSILON && fabsf(cam->rotation.y) < EPSILON
		&& fabsf(cam->rotation.z) < EPSILON)
		cam->rotation = create_vector(0, 0, 1);
	cam->transform = view_transform(cam->position,
			add_tuples(cam->position, cam->rotation), create_vector(0, 1, 0));
	cam->inv_transform = invert_4x4(cam->transform);
	half_view = tan(cam->fov / 2);
	aspect = (float)cam->hsize / (float)cam->vsize;
	if (aspect >= 1)
	{
		cam->half_width = half_view;
		cam->half_height = half_view / aspect;
	}
	else
	{
		cam->half_width = half_view * aspect;
		cam->half_height = half_view;
	}
	cam->pixel_size = (cam->half_width * 2) / cam->hsize;
}

// Builds the ambient term from material color, ambient color, and ambient ratio
t_color	ambient_from_world(t_lighting lighting, t_ambient *amb)
{
	t_color	ambient_color;
	t_color	blended;
	float	f;

	ambient_color = color_from_rgb(amb->cr, amb->cg, amb->cb);
	f = amb->al_ratio;
	blended.r = lighting.material.color.r * (1.0f - f) + ambient_color.r * f;
	blended.g = lighting.material.color.g * (1.0f - f) + ambient_color.g * f;
	blended.b = lighting.material.color.b * (1.0f - f) + ambient_color.b * f;
	return (multiply_colors(blended, lighting.material.ambient * f));
}

// Initializes the world space used to create a scene
// Moving all the values that were parsed into the actual objects
// (i aint reworking the parser again 😒)
void	new_world(t_world *w)
{
	camera(w->cam);
	w->l->light.p_light = point_light(create_point(w->l->px, w->l->py,
				w->l->pz), multiply_colors(color_from_rgb(w->l->cr,
					w->l->cg, w->l->cb), w->l->emission));
	if (w->sp)
		init_spheres(w->sp);
	if (w->pl)
		init_planes(w->pl);
	if (w->cy)
		init_cylinders(w->cy);
}
