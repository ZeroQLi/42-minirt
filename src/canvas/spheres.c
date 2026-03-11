/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:49:27 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/11 15:21:49 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_sphere	*create_sphere(void)
{
	t_sphere	*sphere;

	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->transform = create_identity();
	return (sphere);
}

void	set_transform(t_sphere *sphere, t_matrix4 transform)
{
	sphere->transform = transform;
}
