/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:31:44 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/05 05:21:23 by nanasser         ###   ########.fr       */
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

typedef struct s_intersection_list
{
	int				count;
	t_intersection	*items;
}	t_intersection_list;

t_ray				create_ray(t_tuple origin, t_tuple direction);
t_tuple				position(t_ray ray, float t);
t_intersection_list	*intersect_sphere(t_ray ray, t_sphere *sphere);
t_intersection		intersect(float t, t_sphere *sphere);
t_intersection_list	*intersection_list(t_intersection i1, t_intersection i2);
t_intersection		hit(t_intersection_list *xs);

t_sphere			*create_sphere(void);


#endif