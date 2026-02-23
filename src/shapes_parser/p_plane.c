/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:10:17 by nanasser          #+#    #+#             */
/*   Updated: 2026/01/08 21:10:17 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/macros.h"
#include "../../includes/shapes.h"

int	parse_plane(char **t, t_data *d)
{
	t_plane	*pl;

	if (array_len(t) != 4)
		return (error_msg(YES, "Invalid plane format", 0));
	pl = ft_calloc(1, sizeof(t_plane));
	if (!pl)
		return (error_msg(YES, "malloc failure somehow", 0));
	if (!parse_vec3(t[1], &pl->px, &pl->py, &pl->pz)
		|| !parse_normal(t[2], &pl->rx, &pl->ry, &pl->rz)
		|| !parse_rgb(t[3], &pl->cr, &pl->cg, &pl->cb))
	{
		free(pl);
		return (error_msg(YES, "Invalid plane format", 0));
	}
	add_plane(d->elements, pl);
	return (1);
}
