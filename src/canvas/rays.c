/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:30:49 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/23 16:34:01 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_ray	create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.dir = direction;
	return (ray);
}

t_tuple	position(t_ray ray, float t)
{
	t_tuple	scaled_dir;
	scaled_dir = scalar_multiply(ray.dir, t);
	return (add_tuples(ray.origin, scaled_dir));
}