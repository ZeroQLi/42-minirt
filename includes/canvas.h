/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:31:44 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/01 06:30:26 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include "tuples.h" 

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	dir;
}	t_ray;

typedef struct s_intersection
{
	float	t;
	void	*object;
}	t_intersection;

t_ray			create_ray(t_tuple origin, t_tuple direction);
t_tuple			position(t_ray ray, float t);
float			*intersect_sphere(t_ray ray, t_sphere *sphere);
t_intersection	intersect(float t, t_sphere *sphere);
t_intersection	*intersection_list(t_intersection i1, t_intersection i2);

t_sphere	*create_sphere(void);


#endif