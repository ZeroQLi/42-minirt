/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:31:44 by mtangalv          #+#    #+#             */
/*   Updated: 2026/04/01 00:39:08 by nanasser         ###   ########.fr       */
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

typedef struct s_intersection_node
{
	t_intersection				value;
	struct s_intersection_node	*next;
}	t_intersection_node;

typedef struct s_intersection_list
{
	t_intersection_node	*head;
	t_intersection_node	*tail;
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
bool				intersect_sphere(t_intersection_list *acc, t_ray ray,
						t_sphere *sphere);
bool				intersect_plane(t_intersection_list *acc, t_ray ray,
						t_plane *plane);
bool				intersect_cylinder(t_intersection_list *acc, t_ray ray,
						t_cylinder *cylinder);
t_intersection		intersect(float t, void *object, t_type type);
t_intersection_list	*intersect_list(t_intersection i1, t_intersection i2);
bool				intersections_push(t_intersection_list *xs,
						t_intersection value);
t_intersection		hit(t_intersection_list *xs);
t_intersection_list	*intersections_joined(t_intersection_list *s1,
						t_intersection_list *s2);
t_intersection_list	*free_intersections(t_intersection_list *xs);

// shadow hit helpers
bool				shadow_hit_sphere(t_ray ray, t_sphere *sphere,
						float max_t);
bool				shadow_hit_plane(t_ray ray, t_plane *plane,
						float max_t);
bool				shadow_hit_cylinder(t_ray ray, t_cylinder *cylinder,
						float max_t);
bool				shadow_hit_sphere_bonus(t_ray ray, t_sphere *sphere,
						float max_t);
bool				shadow_hit_plane_bonus(t_ray ray, t_plane *plane,
						float max_t);
bool				shadow_hit_cylinder_bonus(t_ray ray, t_cylinder *cylinder,
						float max_t);

// reflection operations
t_tuple				normal_at(void *object, t_type type, t_tuple world_point);
t_tuple				reflect(t_tuple vector, t_tuple normal);

t_material			material_at(void *object, t_type type);
t_precomp			prepare_computation(t_intersection i, t_ray ray);

#endif