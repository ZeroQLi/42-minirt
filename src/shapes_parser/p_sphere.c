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
#include "../../includes/macros.h"

int	parse_sphere(char **t, t_data *d)
{
	t_sphere	*sp;

	if (array_len(t) != 4)
		return (error_msg("Invalid sphere format", 0));
	sp = malloc(sizeof(t_sphere));
	if (!sp)
		return (0);
	sp->diameter = ft_atof(t[2]);
	if (!parse_vec3(t[1], &sp->px, &sp->py, &sp->pz)
		|| sp->diameter <= 0 || !parse_rgb(t[3], &sp->cr, &sp->cg, &sp->cb))
	{
		free(sp);
		return (0);
	}
	d->elements->sp = sp;
	return (1);
}
