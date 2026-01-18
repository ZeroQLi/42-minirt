/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:10:32 by nanasser          #+#    #+#             */
/*   Updated: 2026/01/08 21:10:32 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/macros.h"

int	parse_cylinder(char **t, t_data *d)
{
	t_cylinder	*cy;

	if (array_len(t) != 6)
		return (error_msg(YES, "Invalid cylinder format", 0));
	cy = ft_calloc(1, sizeof(t_cylinder));
	if (!cy)
		return (0);
	cy->diameter = ft_atof(t[3]);
	cy->height = ft_atof(t[4]);
	if (!parse_vec3(t[1], &cy->px, &cy->py, &cy->pz) || !parse_normal(t[2],
		&cy->rx, &cy->ry, &cy->rz) || cy->diameter <= 0 || cy->height <= 0
		|| !parse_rgb(t[5], &cy->cr, &cy->cg, &cy->cb))
	{
		free(cy);
		return (0);
	}
	add_cylinder(d->elements, cy);
	return (1);
}
