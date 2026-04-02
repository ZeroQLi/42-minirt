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

int	parse_light(char **t, t_data *d)
{
	t_light	*l;

	if (array_len(t) != 4)
		return (error_msg(YES, "Light format must be: " L_FORMAT, 0));
	else if (d->light_exists)
		return (error_msg(YES, MULTIPLE_LIGHT_ERR, 0));
	if (!ft_isdigit_str(t[2]))
		return (error_msg(YES, "Light brightness value must be a valid number",
				0));
	d->light_exists = YES;
	l = ft_calloc(1, sizeof(t_light));
	if (!l)
		return (error_msg(YES, "alloc fail? if only ram didnt cost a LUNG", 0));
	l->emission = ft_atof(t[2]);
	if (!parse_vec3(t[1], &l->px, &l->py, &l->pz) || l->emission < 0.0
		|| l->emission > 1.0 || !parse_rgb(t[3], &l->cr, &l->cg, &l->cb))
	{
		if (l->emission < 0.0 || l->emission > 1.0)
			error_msg(YES, "Light brightness value must be between 0-1", 0);
		free(l);
		return (error_msg(NO, "Invalid light format", 0));
	}
	d->world->l = l;
	return (1);
}
