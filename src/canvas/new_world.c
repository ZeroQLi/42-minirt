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

// Initializes the world space used to create a scene
// Moving all the values that were parsed into the actual objects
// (i aint reworking the parser again 😒)
void	new_world(t_world *w)
{
	t_sphere	*tmp;

	if (w->l)
	{
		w->l->light.p_light = point_light(create_point(w->l->px, w->l->py,
					w->l->pz), create_color(1, 1, 1));
	}
	if (w->sp)
	{
		tmp = w->sp;
		// while (w->sp->next != NULL)
		// {
			tmp->position = create_point(tmp->px, tmp->py, tmp->pz);
			tmp->material = create_material(tmp);
		// }
		// w->sp = w->sp->next;
	}
	if (tmp->next)
	{
		tmp = w->sp->next;
		tmp->position = create_point(tmp->px, tmp->py, tmp->pz);
		tmp->material = create_material(tmp);
		set_transform(tmp, scaling(0.5, 0.5, 0.5));
	}
}
