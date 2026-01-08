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
#include "../../includes/macros.h"

int	parse_ambient(char **t, t_data *d)
{
	t_ambient	*amb;

	if (array_len(t) != 3)
		return (error_msg("Invalid ambient format", 0));
	amb = malloc(sizeof(t_ambient));
	if (!amb)
		return (0);
	if (!parse_ratio(t[1], &amb->al_ratio) || !parse_rgb(t[2], &amb->cr,
			&amb->cg, &amb->cb) || !in_range(amb->al_ratio, 0.0, 1.0))
	{
		free(amb);
		return (0);
	}
	d->elements->amb = amb;
	return (1);
}
