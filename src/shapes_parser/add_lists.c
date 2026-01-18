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
#include "../../includes/macros.h"

// FOR BONUS //
// void	add_light(t_elements *e, t_light *new)
// {
// 	t_light	*tmp;

// 	if (!e->l)
// 	{
// 		e->l = new;
// 		return ;
// 	}
// 	tmp = e->l;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new;
// }

void	add_plane(t_elements *e, t_plane *new)
{
	t_plane	*tmp;

	if (!e->pl)
	{
		e->pl = new;
		return ;
	}
	tmp = e->pl;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_cylinder(t_elements *e, t_cylinder *new)
{
	t_cylinder	*tmp;

	if (!e->cy)
	{
		e->cy = new;
		return ;
	}
	tmp = e->cy;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_sphere(t_elements *e, t_sphere *new)
{
	t_sphere	*tmp;

	if (!e->sp)
	{
		e->sp = new;
		return ;
	}
	tmp = e->sp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
