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

int	parse_cylinder(char **t, t_data *d)
{
	t_cylinder	*cy;

	if (array_len(t) != 6)
		return (error_msg(YES, "Cylinder format must be: " CY_FORMAT, 0));
	if (!ft_isdigit_str(t[3]) || !ft_isdigit_str(t[4]))
		return (error_msg(YES, "Diameter & Height values must be a valid number\
", 0));
	cy = ft_calloc(1, sizeof(t_cylinder));
	if (!cy)
		return (error_msg(YES, "malloc fail *sigh* yes i sighed in text", 0));
	cy->diameter = ft_atof(t[3]) / 2;
	cy->height = ft_atof(t[4]) / 2;
	if (!parse_vec3(t[1], &cy->px, &cy->py, &cy->pz) || !parse_normal(t[2],
			&cy->rx, &cy->ry, &cy->rz) || cy->diameter <= 0 || cy->height <= 0
		|| !parse_rgb(t[5], &cy->cr, &cy->cg, &cy->cb))
	{
		if (cy->diameter <= 0)
			error_msg(YES, "Cylinder size must be bigger than 0", 0);
		if (cy->height <= 0)
			error_msg(YES, "Cylinder height must be bigger than 0", 0);
		free(cy);
		return (error_msg(NO, "Invalid cylinder format", 0));
	}
	add_cylinder(d->world, cy);
	return (1);
}
