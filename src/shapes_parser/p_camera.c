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
#include <stdio.h>

int	parse_camera(char **t, t_data *d)
{
	t_camera	*cam;

	if (array_len(t) != 4)
		return (error_msg("Invalid camera format", 0));
	else if (d->cam_exists)
		return (error_msg(MULTIPLE_CAMERA_ERR, 0));
	d->cam_exists = YES;
	cam = ft_calloc(1, sizeof(t_camera));
	if (!cam)
		return (0);
	cam->fov = ft_atoi(t[3]);
	if (!parse_vec3(t[1], &cam->px, &cam->py, &cam->pz) || !parse_normal(t[2],
		&cam->rx, &cam->ry, &cam->rz) || cam->fov < 0 || cam->fov > 180)
	{
		free(cam);
		return (0);
	}
	printf("\n%f\n\n\n\n\n", cam->px);
	d->elements->cam = cam;
	return (1);
}
