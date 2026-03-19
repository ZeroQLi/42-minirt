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

static t_intersection_list	*intersect_shape(t_ray r, void *object, t_type type)
{
	if (type == SPHERE)
		return (intersect_sphere(r, (t_sphere *)object));
	else if (type == PLANE)
		return (intersect_plane(r, (t_plane *)object));
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

// static t_intersection_list	*intersect_cylinder_list(t_cylinder *head, t_ray r,
// 	t_intersection_list *acc)
// {
// 	t_intersection_list	*curr;
// 	t_cylinder			*cy;

// 	cy = head;
// 	while (cy)
// 	{
// 		curr = intersect_shape(r, cy, CYLINDER);
// 		if (curr && (acc = intersections_joined(acc, curr)) == NULL)
// 			return (NULL);
// 		cy = cy->next;
// 	}
// 	return (acc);
// }

static t_intersection_list	*intersect_shape_list(void *head, t_type type,
	t_ray r, t_intersection_list *acc)
{
	if (type == SPHERE)
		return (intersect_sphere_list((t_sphere *)head, r, acc));
	else if (type == PLANE)
		return (intersect_plane_list((t_plane *)head, r, acc));
	// else if (type == CYLINDER)
	// 	return (intersect_cylinder_list((t_cylinder *)head, r, acc));
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
	// acc = intersect_shape_list(w->cy, CYLINDER, r, acc);
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
	cam->rotation = create_vector(cam->rx, cam->ry, cam->rz);
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

// Initializes the world space used to create a scene
// Moving all the values that were parsed into the actual objects
// (i aint reworking the parser again 😒)
void	new_world(t_world *w)
{
	t_sphere	*tmp;
	t_plane		*tmp_pl;

	camera(w->cam);
	if (w->l)
	{
		w->l->light.p_light = point_light(create_point(w->l->px, w->l->py,
					w->l->pz), color_from_rgb(w->l->cr, w->l->cg, w->l->cb));
	}
	if (w->sp)
	{
		tmp = w->sp;
		while (tmp)
		{
			tmp->position = create_point(tmp->px, tmp->py, tmp->pz);
			tmp->material = create_material(tmp->cr, tmp->cg, tmp->cb);
			set_transform(&tmp->tf, translation(tmp->position.x,
					tmp->position.y, tmp->position.z));
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
			tmp_pl->rotation = create_vector(tmp_pl->rx, tmp_pl->ry, tmp_pl->rz);
			tmp_pl->material = create_material(tmp_pl->cr, tmp_pl->cg,
					tmp_pl->cb);
			transform = translation(tmp_pl->position.x, tmp_pl->position.y,
					tmp_pl->position.z);
			transform = matrix_multiply(transform, rotation_x((M_PI / 2)
					* tmp_pl->rotation.x));
			transform = matrix_multiply(transform, rotation_y((M_PI / 2)
					* tmp_pl->rotation.y));
			transform = matrix_multiply(transform, rotation_z((M_PI / 2)
					* tmp_pl->rotation.z));
			set_transform(&tmp_pl->tf, transform);
			tmp_pl = tmp_pl->next;
		}
	}
}
