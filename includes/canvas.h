/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:31:44 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/18 22:12:32 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include "minirt.h"
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

typedef struct s_precomp
{
	float	t;
	void	*object;
	t_type	type;
	t_tuple	point;
	t_tuple	over_point;
	t_tuple	eyev;
	t_tuple	normalv;
	bool	inside;
}	t_precomp;

// ray operations
t_ray				create_ray(t_tuple origin, t_tuple direction);
t_tuple				position(t_ray ray, float t);
t_ray				transform_ray(t_ray ray, t_matrix4 matrix);

// intersection operations
t_intersection_list	*intersect_sphere(t_ray ray, t_sphere *sphere);
t_intersection		intersect(float t, void *object, t_type type);
t_intersection_list	*intersect_list(t_intersection i1, t_intersection i2);
t_intersection		hit(t_intersection_list *xs);
t_intersection_list	*intersections_joined(t_intersection_list *s1,
						t_intersection_list *s2);
void				sort_intersections(t_intersection_list *xs);

// reflection operations
t_tuple				normal_at(void *object, t_type type, t_tuple world_point);
t_tuple				reflect(t_tuple vector, t_tuple normal);

#endif