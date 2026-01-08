/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:09:18 by nanasser          #+#    #+#             */
/*   Updated: 2026/01/08 21:09:18 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/macros.h"

int	parse_camera(char **t, t_data *d)
{
	t_camera	*cam;

	if (array_len(t) != 4)
		return (error_msg("Invalid camera format", 0));
	cam = malloc(sizeof(t_camera));
	if (!cam)
		return (0);
	if (!parse_vec3(t[1], &cam->px, &cam->py, &cam->pz) || !parse_normal(t[2],
			&cam->rx, &cam->ry, &cam->rz) || !parse_fov(t[3], &cam->fov))
	{
		free(cam);
		return (0);
	}
	d->elements->cam = cam;
	return (1);
}
