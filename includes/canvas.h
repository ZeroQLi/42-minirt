/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:31:44 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/12 14:59:54 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include "tuples.h" 

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

typedef struct s_intersection
{
	float	t;
	void	*object;
	t_type	type;
}	t_intersection;

typedef struct s_intersection_list
{
	int				count;
	t_intersection	*items;
}	t_intersection_list;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	dir;
}	t_ray;

t_ray				create_ray(t_tuple origin, t_tuple direction);
t_tuple				position(t_ray ray, float t);
t_ray				transform_ray(t_ray ray, t_matrix4 matrix);

t_intersection_list	*intersect_sphere(t_ray ray, t_sphere *sphere);
t_intersection		intersect(float t, void *object, t_type type);
t_intersection_list	*intersect_list(t_intersection i1, t_intersection i2);
t_intersection		hit(t_intersection_list *xs);

t_tuple				normal_at(t_sphere *sphere, t_tuple world_point);
t_tuple				reflect(t_tuple vector, t_tuple normal);
#endif