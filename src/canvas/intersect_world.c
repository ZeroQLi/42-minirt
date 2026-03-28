/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 16:33:47 by nanasser          #+#    #+#             */
/*   Updated: 2026/03/28 16:33:47 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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
