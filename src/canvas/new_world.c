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
	return (intersect_list(intersect(0, NULL, 0), intersect(0, NULL, 0)));
}

t_intersection_list	*intersect_world(t_world *w, t_ray r)
{
	t_intersection_list	*acc;
	t_intersection_list	*curr;
	t_sphere			*tmp;

	acc = intersect_list(intersect(0, NULL, 0), intersect(0, NULL, 0));
	if (!acc)
		return (NULL);
	tmp = w->sp;
	while (tmp)
	{
		curr = intersect_shape(r, tmp, SPHERE);
		if (curr)
		{
			acc = intersections_joined(acc, curr);
			if (!acc)
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (acc);
}

static void	camera(t_camera *cam)
{
	float	half_view;
	float	aspect;

	cam->hsize = WIN_WIDTH;
	cam->vsize = WIN_HEIGHT;
	cam->fov *= (M_PI / 180);
	cam->position = create_point(cam->px, cam->py, cam->pz);
	cam->rotation = create_point(cam->rx, cam->ry, cam->rz);
	cam->transform = view_transform(cam->position,
		cam->rotation, create_point(0, 1, 0));
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
	// t_plane		*tmp_pl;

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
	// if (w->pl)
	// {
	// 	tmp_pl = w->pl;
	// 	while (tmp_pl->next != NULL)
	// 	{
	// 		tmp_pl->position = create_point(tmp_pl->px, tmp_pl->py, tmp_pl->pz);
	// 		tmp_pl->material = create_material(tmp_pl->cr, tmp_pl->cg,
	// 				tmp_pl->cb);
	// 		set_transform(&tmp_pl->tf, translation(tmp_pl->position.x,
	// 				tmp_pl->position.y, tmp_pl->position.z));
	// 	}
	// }
}
