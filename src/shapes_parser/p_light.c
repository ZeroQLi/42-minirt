/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:09:37 by nanasser          #+#    #+#             */
/*   Updated: 2026/01/08 21:09:37 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/macros.h"

int	parse_light(char **t, t_data *d)
{
	t_light	*l;

	if (array_len(t) != 4)
		return (error_msg(YES, "Invalid light format", 0));
	else if (d->light_exists)
		return (error_msg(YES, MULTIPLE_LIGHT_ERR, 0));
	d->light_exists = YES;
	l = ft_calloc(1, sizeof(t_light));
	if (!l)
		return (error_msg(YES, "alloc fail? if only ram didnt cost a LUNG", 0));
	l->emission = ft_atof(t[2]);
	if (!parse_vec3(t[1], &l->px, &l->py, &l->pz) || l->emission < 0.0
		|| l->emission > 1.0 || !parse_rgb(t[3], &l->cr, &l->cg, &l->cb))
	{
		free(l);
		return (error_msg(YES, "Invalid light format", 0));
	}
	d->elements->l = l;
	return (1);
}
