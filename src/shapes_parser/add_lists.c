/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:47:04 by nanasser          #+#    #+#             */
/*   Updated: 2026/01/15 04:47:04 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	add_plane(t_world *w, t_plane *new)
{
	t_plane	*tmp;

	if (!w->pl)
	{
		w->pl = new;
		new->next = NULL;
		return ;
	}
	tmp = w->pl;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
}

void	add_cylinder(t_world *w, t_cylinder *new)
{
	t_cylinder	*tmp;

	if (!w->cy)
	{
		w->cy = new;
		new->next = NULL;
		return ;
	}
	tmp = w->cy;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
}

void	add_sphere(t_world *w, t_sphere *new)
{
	t_sphere	*tmp;

	if (!w->sp)
	{
		w->sp = new;
		new->next = NULL;
		return ;
	}
	tmp = w->sp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
}
