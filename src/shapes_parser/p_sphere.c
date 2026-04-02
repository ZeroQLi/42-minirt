/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:09:56 by nanasser          #+#    #+#             */
/*   Updated: 2026/01/08 21:09:56 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	parse_sphere(char **t, t_data *d)
{
	t_sphere	*sp;

	if (array_len(t) != 4)
		return (error_msg(YES, "Sphere format must be: " SP_FORMAT, 0));
	if (!ft_isdigit_str(t[2]))
		return (error_msg(YES, "Sphere size must be a valid number", 0));
	sp = ft_calloc(1, sizeof(t_sphere));
	if (!sp)
		return (error_msg(YES, "malloc failure bruh", 0));
	sp->diameter = ft_atof(t[2]) / 2;
	if (!parse_vec3(t[1], &sp->px, &sp->py, &sp->pz)
		|| sp->diameter <= 0 || !parse_rgb(t[3], &sp->cr, &sp->cg, &sp->cb))
	{
		if (sp->diameter <= 0)
			error_msg(YES, "Sphere size must be bigger than 0", 0);
		free(sp);
		return (error_msg(NO, "Invalid sphere format", 0));
	}
	add_sphere(d->world, sp);
	return (1);
}
