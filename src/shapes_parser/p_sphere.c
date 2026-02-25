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
		return (error_msg(YES, "Invalid sphere format", 0));
	sp = ft_calloc(1, sizeof(t_sphere));
	if (!sp)
		return (error_msg(YES, "malloc failure bruh", 0));
	sp->diameter = ft_atof(t[2]);
	if (!parse_vec3(t[1], &sp->px, &sp->py, &sp->pz)
		|| sp->diameter <= 0 || !parse_rgb(t[3], &sp->cr, &sp->cg, &sp->cb))
	{
		free(sp);
		return (error_msg(YES, "Invalid sphere format", 0));
	}
	sp->t_pos = create_point(sp->px, sp->py, sp->pz);
	sp->t_rgb = create_color(sp->cr, sp->cb, sp->cg);
	add_sphere(d->elements, sp);
	return (1);
}
