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

bool	intersections_push(t_intersection_list *xs, t_intersection value)
{
	if (!value.object)
		return (true);
	return (append_intersection(xs, value));
}

// return the closest intersection with a positive t value, or a default
t_intersection	hit(t_intersection_list *xs)
{
	t_intersection_node	*curr;
	t_intersection		best;
	bool				has_hit;

	if (!xs)
		return (intersect(0, NULL, 0));
	curr = xs->head;
	has_hit = false;
	best = intersect(0, NULL, 0);
	while (curr)
	{
		if (curr->value.object != NULL && curr->value.t >= EPSILON
			&& (!has_hit || curr->value.t < best.t))
		{
			best = curr->value;
			has_hit = true;
		}
		curr = curr->next;
	}
	if (!has_hit)
		return (intersect(0, NULL, 0));
	return (best);
}

t_intersection_list	*intersect_world(t_world *w, t_ray r,
			t_intersection_list *acc)
{
	t_world				world;

	world.sp = w->sp;
	while (world.sp && acc)
	{
		if (!intersect_sphere(acc, r, world.sp))
			return (free_intersections(acc));
		world.sp = world.sp->next;
	}
	world.pl = w->pl;
	while (world.pl && acc)
	{
		if (!intersect_plane(acc, r, world.pl))
			return (free_intersections(acc));
		world.pl = world.pl->next;
	}
	world.cy = w->cy;
	while (world.cy && acc)
	{
		if (!intersect_cylinder(acc, r, world.cy))
			return (free_intersections(acc));
		world.cy = world.cy->next;
	}
	return (acc);
}
