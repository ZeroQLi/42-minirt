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

int	parse_camera(char **t, t_data *d)
{
	t_camera	*cam;

	if (array_len(t) != 4)
		return (error_msg(YES, "Camera format must be: " C_FORMAT, 0));
	else if (d->cam_exists)
		return (error_msg(YES, MULTIPLE_CAMERA_ERR, 0));
	d->cam_exists = YES;
	cam = ft_calloc(1, sizeof(t_camera));
	if (!cam)
		return (error_msg(YES, "malloc fail, you know the routine", 0));
	if (!ft_isdigit_str(t[3]))
		return (error_msg(YES, "Camera fov must be a number", 0));
	cam->fov = ft_atoi(t[3]) * (M_PI / 180);
	if (!parse_vec3(t[1], &cam->px, &cam->py, &cam->pz) || !parse_normal(t[2],
			&cam->rx, &cam->ry, &cam->rz) || cam->fov < 0 || cam->fov > 180)
	{
		if (cam->fov < 0 || cam->fov > 180)
			error_msg(YES, "Camera fov must be between 0-180", 0);
		free(cam);
		return (error_msg(NO, "Invalid camera format", 0));
	}
	d->world->cam = cam;
	cam->hsize = WIN_WIDTH;
	cam->vsize = WIN_HEIGHT;
	return (1);
}
