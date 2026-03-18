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
		curr = intersect_sphere(r, tmp);
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

// matrix_multiply(rotation_matrix_from_point(cam->rotation), create_point(0, 1, 0)) // temporary function to come later

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

// static t_sphere	*get_sphere_at(t_sphere *head, int index)
// {
// 	int	i;

// 	i = 0;
// 	while (head && i < index)
// 	{
// 		head = head->next;
// 		i++;
// 	}
// 	return (head);
// }

// static int	ensure_sphere_count(t_world *w, int target)
// {
// 	t_sphere	*new;
// 	int			count;

// 	count = 0;
// 	new = w->sp;
// 	while (new)
// 	{
// 		count++;
// 		new = new->next;
// 	}
// 	while (count < target)
// 	{
// 		new = ft_calloc(1, sizeof(t_sphere));
// 		if (!new)
// 			return (0);
// 		add_sphere(w, new);
// 		count++;
// 	}
// 	return (1);
// }

// static void	build_chapter_scene(t_world *w)
// {
// 	t_sphere	*floor;
// 	t_sphere	*left_wall;
// 	t_sphere	*right_wall;
// 	t_sphere	*middle;
// 	t_sphere	*right;
// 	t_sphere	*left;
// 	t_matrix4	t;

// 	if (!ensure_sphere_count(w, 6))
// 		return ;
// 	floor = get_sphere_at(w->sp, 0);
// 	left_wall = get_sphere_at(w->sp, 1);
// 	right_wall = get_sphere_at(w->sp, 2);
// 	middle = get_sphere_at(w->sp, 3);
// 	right = get_sphere_at(w->sp, 4);
// 	left = get_sphere_at(w->sp, 5);
// 	floor->position = create_point(0, 0, 0);
// 	left_wall->position = create_point(0, 0, 0);
// 	right_wall->position = create_point(0, 0, 0);
// 	middle->position = create_point(0, 0, 0);
// 	right->position = create_point(0, 0, 0);
// 	left->position = create_point(0, 0, 0);
// 	set_transform(floor, scaling(10, 0.01f, 10));
// 	floor->material = create_material(floor);
// 	floor->material.color = create_color(1, 0.9f, 0.9f);
// 	floor->material.specular = 0;
// 	t = matrix_multiply(translation(0, 0, 5), rotation_y(-(M_PI / 4)));
// 	t = matrix_multiply(t, rotation_x(M_PI / 2));
// 	t = matrix_multiply(t, scaling(10, 0.01f, 10));
// 	set_transform(left_wall, t);
// 	left_wall->material = floor->material;
// 	t = matrix_multiply(translation(0, 0, 5), rotation_y(M_PI / 4));
// 	t = matrix_multiply(t, rotation_x(M_PI / 2));
// 	t = matrix_multiply(t, scaling(10, 0.01f, 10));
// 	set_transform(right_wall, t);
// 	right_wall->material = floor->material;
// 	set_transform(middle, translation(-0.5f, 1, 0.5f));
// 	middle->material = create_material(middle);
// 	middle->material.color = create_color(0.1f, 1, 0.5f);
// 	middle->material.diffuse = 0.7f;
// 	middle->material.specular = 0.3f;
// 	t = matrix_multiply(translation(1.5f, 0.5f, -0.5f),
// 			scaling(0.5f, 0.5f, 0.5f));
// 	set_transform(right, t);
// 	right->material = create_material(right);
// 	right->material.color = create_color(0.5f, 1, 0.1f);
// 	right->material.diffuse = 0.7f;
// 	right->material.specular = 0.3f;
// 	t = matrix_multiply(translation(-1.5f, 0.33f, -0.75f),
// 			scaling(0.33f, 0.33f, 0.33f));
// 	set_transform(left, t);
// 	left->material = create_material(left);
// 	left->material.color = create_color(1, 0.8f, 0.1f);
// 	left->material.diffuse = 0.7f;
// 	left->material.specular = 0.3f;
// }

// static void	setup_scene_light(t_world *w)
// {
// 	if (!w->l)
// 	{
// 		w->l = ft_calloc(1, sizeof(t_light));
// 		if (!w->l)
// 			return ;
// 	}
// 	w->l->light.p_light = point_light(create_point(w->l->px, w->l->py, w->l->pz),
// 			color_from_rgb(w->l->cr, w->l->cg, w->l->cb));
// }

// // Initializes the world space used to create a scene
// // Moving all the values that were parsed into the actual objects
// // (i aint reworking the parser again 😒)
// void	new_world(t_world *w)
// {
// 	if (!w || !w->cam)
// 		return ;
// 	camera(w->cam);
// 	setup_scene_light(w);
// 	build_chapter_scene(w);
// }