/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:53:55 by nanasser          #+#    #+#             */
/*   Updated: 2026/01/18 19:53:55 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	free_planes(t_plane *pl)
{
	t_plane	*next;

	while (pl)
	{
		next = pl->next;
		free(pl);
		pl = next;
	}
	pl = NULL;
}

void	free_cylinders(t_cylinder *cy)
{
	t_cylinder	*next;

	while (cy)
	{
		next = cy->next;
		free(cy);
		cy = next;
	}
	cy = NULL;
}

void	free_spheres(t_sphere *sp)
{
	t_sphere	*next;

	while (sp)
	{
		next = sp->next;
		free(sp);
		sp = next;
	}
	sp = NULL;
}

void	free_all_shapes(t_world *w)
{
	free_spheres(w->sp);
	free_cylinders(w->cy);
	free_planes(w->pl);
}
