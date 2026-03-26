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

static t_matrix4	align_y_to_vector(t_tuple axis)
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

static t_intersection_list	*intersect_shape(t_ray r, void *object, t_type type)
{
	if (type == SPHERE)
		return (intersect_sphere(r, (t_sphere *)object));
	else if (type == PLANE)
		return (intersect_plane(r, (t_plane *)object));
	else if (type == CYLINDER)
		return (intersect_cylinder(r, (t_cylinder *)object));
	return (intersect_list(intersect(0, NULL, 0), intersect(0, NULL, 0)));
}

static t_intersection_list	*intersect_sphere_list(t_sphere *head, t_ray r,
	t_intersection_list *acc)
{
	t_intersection_list	*curr;
	t_sphere			*sp;

	sp = head;
	while (sp)
	{
		curr = intersect_shape(r, sp, SPHERE);
		acc = intersections_joined(acc, curr);
		if (curr && acc == NULL)
			return (NULL);
		sp = sp->next;
	}
	return (acc);
}

static t_intersection_list	*intersect_plane_list(t_plane *head, t_ray r,
	t_intersection_list *acc)
{
	t_intersection_list	*curr;
	t_plane				*pl;

	pl = head;
	while (pl)
	{
		curr = intersect_shape(r, pl, PLANE);
		acc = intersections_joined(acc, curr);
		if (curr && acc == NULL)
			return (NULL);
		pl = pl->next;
	}
	return (acc);
}

static t_intersection_list	*intersect_cylinder_list(t_cylinder *head, t_ray r,
	t_intersection_list *acc)
{
	t_intersection_list	*curr;
	t_cylinder			*cy;

	cy = head;
	while (cy)
	{
		curr = intersect_shape(r, cy, CYLINDER);
		acc = intersections_joined(acc, curr);
		if (curr && acc == NULL)
			return (NULL);
		cy = cy->next;
	}
	return (acc);
}

t_intersection_list	*intersect_world(t_world *w, t_ray r)
{
	t_intersection_list	*acc;

	acc = intersect_list(intersect(0, NULL, 0), intersect(0, NULL, 0));
	if (!acc)
		return (NULL);
	acc = intersect_sphere_list(w->sp, r, acc);
	if (!acc)
		return (NULL);
	acc = intersect_plane_list(w->pl, r, acc);
	if (!acc)
		return (NULL);
	acc = intersect_cylinder_list(w->cy, r, acc);
	if (!acc)
		return (NULL);
	sort_intersections(acc);
	return (acc);
}

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

t_color	ambient_from_world(t_lighting lighting, t_ambient *amb)
{
	t_color	ambient_color;

	ambient_color = color_from_rgb(amb->cr, amb->cg, amb->cb);
	return (multiply_colors(hadamard_product(lighting.material.color,
				ambient_color), lighting.material.ambient * amb->al_ratio));
}

static void	init_spheres(t_sphere *sp)
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

static void	init_planes(t_plane *pl)
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

static void	init_cylinders(t_cylinder *cy)
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
