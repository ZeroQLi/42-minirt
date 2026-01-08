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
		return (error_msg("Invalid light format", 0));
	l = malloc(sizeof(t_light));
	if (!l)
		return (0);
	if (!parse_vec3(t[1], &l->px, &l->py, &l->pz) || !parse_ratio(t[2],
			&l->emission) || !parse_rgb(t[3], &l->cr, &l->cg, &l->cb))
	{
		free(l);
		return (0);
	}
	d->elements->l = l;
	return (1);
}
