/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:49:27 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/13 07:39:33 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	set_transform(t_sphere *sphere, t_matrix4 transform)
{
	sphere->transform = transform;
	sphere->inv_transform = invert_4x4(transform);
}
