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

// Initializes the world space used to create a scene
// Moving all the values that were parsed into the actual objects
// (i aint reworking the parser again 😒)
void	new_world(t_world *w)
{
	t_sphere	*tmp;

	if (w->l)
	{
		w->l->light.p_light.position = create_point(w->l->px, w->l->py, w->l->pz);
		w->l->light.p_light.intensity = color_from_rgb(w->l->cr, w->l->cg, w->l->cb);
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
