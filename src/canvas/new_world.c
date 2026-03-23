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

	// Build an orthonormal basis so local +Y aligns with parsed normal/direction.
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
		if (curr && (acc = intersections_joined(acc, curr)) == NULL)
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
		if (curr && (acc = intersections_joined(acc, curr)) == NULL)
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
		if (curr && (acc = intersections_joined(acc, curr)) == NULL)
			return (NULL);
		cy = cy->next;
	}
	return (acc);
}

static t_intersection_list	*intersect_shape_list(void *head, t_type type,
	t_ray r, t_intersection_list *acc)
{
	if (type == SPHERE)
		return (intersect_sphere_list((t_sphere *)head, r, acc));
	else if (type == PLANE)
		return (intersect_plane_list((t_plane *)head, r, acc));
	else if (type == CYLINDER)
		return (intersect_cylinder_list((t_cylinder *)head, r, acc));
	return (acc);
}

t_intersection_list	*intersect_world(t_world *w, t_ray r)
{
	t_intersection_list	*acc;
	acc = intersect_list(intersect(0, NULL, 0), intersect(0, NULL, 0));
	if (!acc)
		return (NULL);
	acc = intersect_shape_list(w->sp, SPHERE, r, acc);
	if (!acc)
		return (NULL);
	acc = intersect_shape_list(w->pl, PLANE, r, acc);
	if (!acc)
		return (NULL);
	acc = intersect_shape_list(w->cy, CYLINDER, r, acc);
	if (!acc)
		return (NULL);
	return (acc);
}

static void	camera(t_camera *cam)
{
	float	half_view;
	float	aspect;
	t_tuple	look_at;

	cam->hsize = WIN_WIDTH;
	cam->vsize = WIN_HEIGHT;
	cam->fov *= (M_PI / 180);
	cam->position = create_point(cam->px, cam->py, cam->pz);
	cam->rotation = scalar_normalize(create_vector(cam->rx, cam->ry, cam->rz));
	if (fabsf(cam->rotation.x) < EPSILON && fabsf(cam->rotation.y) < EPSILON
		&& fabsf(cam->rotation.z) < EPSILON)
		cam->rotation = create_vector(0, 0, 1);
	look_at = add_tuples(cam->position, cam->rotation);
	cam->transform = view_transform(cam->position,
		look_at, create_vector(0, 1, 0));
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

// Initializes the world space used to create a scene
// Moving all the values that were parsed into the actual objects
// (i aint reworking the parser again 😒)
void	new_world(t_world *w)
{
	t_sphere	*tmp;
	t_plane		*tmp_pl;
	t_cylinder	*tmp_cyl;

	camera(w->cam);
	w->l->light.p_light = point_light(create_point(w->l->px, w->l->py,
				w->l->pz), multiply_colors(color_from_rgb(w->l->cr,
					w->l->cg, w->l->cb), w->l->emission));
	if (w->sp)
	{
		tmp = w->sp;
		while (tmp)
		{
			t_matrix4	transform;

			tmp->position = create_point(tmp->px, tmp->py, tmp->pz);
			tmp->material = create_material(tmp->cr, tmp->cg,
					tmp->cb);
			transform = translation(tmp->position.x, tmp->position.y,
					tmp->position.z);
			transform = matrix_multiply(transform, scaling(tmp->diameter,
					tmp->diameter, tmp->diameter));
			set_transform(&tmp->tf, transform);
			tmp = tmp->next;
		}
	}
	if (w->pl)
	{
		t_matrix4	transform;

		tmp_pl = w->pl;
		while (tmp_pl)
		{
			tmp_pl->position = create_point(tmp_pl->px, tmp_pl->py, tmp_pl->pz);
			tmp_pl->rotation = scalar_normalize(create_vector(tmp_pl->rx,
						tmp_pl->ry, tmp_pl->rz));
			tmp_pl->material = create_material(tmp_pl->cr, tmp_pl->cg,
				tmp_pl->cb);
			transform = translation(tmp_pl->position.x, tmp_pl->position.y,
					tmp_pl->position.z);
			transform = matrix_multiply(transform,
					align_y_to_vector(tmp_pl->rotation));
			set_transform(&tmp_pl->tf, transform);
			tmp_pl = tmp_pl->next;
		}
	}
	if (w->cy)
	{
		tmp_cyl = w->cy;
		while (tmp_cyl)
		{
			t_matrix4	transform;

			tmp_cyl->position = create_point(tmp_cyl->px, tmp_cyl->py, tmp_cyl->pz);
			tmp_cyl->rotation = scalar_normalize(create_vector(tmp_cyl->rx,
						tmp_cyl->ry, tmp_cyl->rz));
			tmp_cyl->material = create_material(tmp_cyl->cr, tmp_cyl->cg,
					tmp_cyl->cb);
			transform = translation(tmp_cyl->position.x, tmp_cyl->position.y,
					tmp_cyl->position.z);
			transform = matrix_multiply(transform,
					align_y_to_vector(tmp_cyl->rotation));
			transform = matrix_multiply(transform, scaling(tmp_cyl->diameter,
					1.0f, tmp_cyl->diameter));
			set_transform(&tmp_cyl->tf, transform);
			tmp_cyl->closed = YES;
			tmp_cyl = tmp_cyl->next;
		}
	}
}
