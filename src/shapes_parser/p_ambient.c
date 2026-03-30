/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:55:04 by nanasser          #+#    #+#             */
/*   Updated: 2026/01/08 20:55:04 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	parse_ambient(char **t, t_data *d)
{
	t_ambient	*amb;

	if (array_len(t) != 3)
		return (error_msg(YES, "Ambient format must be: " A_FORMAT, 0));
	else if (d->amb_exists)
		return (error_msg(YES, MULTIPLE_AMBIENT_ERR, 0));
	d->amb_exists = YES;
	amb = ft_calloc(1, sizeof(t_ambient));
	if (!amb)
		return (error_msg(YES, "malloc FAILED!", 0));
	if (!ft_isdigit_str(t[1]))
		return (error_msg(YES, "Ambient ratio must be a valid number", 0));
	amb->al_ratio = ft_atof(t[1]);
	if (amb->al_ratio < 0.0 || amb->al_ratio > 1.0
		|| !parse_rgb(t[2], &amb->cr, &amb->cg, &amb->cb))
	{
		if (amb->al_ratio < 0.0 || amb->al_ratio > 1.0)
			error_msg(YES, "Ambient ration must be between 0-1", 0);
		free(amb);
		return (error_msg(NO, "Invalid ambient format", 0));
	}
	d->world->amb = amb;
	return (1);
}
