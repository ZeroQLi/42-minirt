/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 14:03:05 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/18 06:33:09 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Intersects a ray with a sphere, returns the intersection points (t values).
t_intersection_list	*intersect_sphere(t_ray ray, t_sphere *sphere)
{
	t_tuple				sphere_to_ray;
	float				a;
	float				b;
	float				disc;
	float				intersections[3];

	ray = transform_ray(ray, sphere->inv_transform);
	sphere_to_ray = sub_tuples(ray.origin, sphere->position);
	a = dot_product(ray.dir, ray.dir);
	b = 2.f * dot_product(ray.dir, sphere_to_ray);
	disc = (b * b) - (4.f * a * (dot_product(sphere_to_ray, sphere_to_ray) - 1.f));
	if (disc < 0)
		return (intersect_list(intersect(0, NULL, 0), intersect(0, NULL, 0)));
	else
	{
		intersections[0] = 2;
		intersections[1] = (-b - sqrtf(disc)) / (2.f * a);
		intersections[2] = (-b + sqrtf(disc)) / (2.f * a);
	}
	return (intersect_list(intersect(intersections[1], sphere, SPHERE),
			intersect(intersections[2], sphere, SPHERE)));
}

// Creates an intersection object with the given t value and sphere reference.
t_intersection	intersect(float t, void *object, t_type type)
{
	t_intersection	i;

	i.t = t;
	i.object = object;
	i.type = type;
	return (i);
}

// Creates an intersection list containing two intersections.
t_intersection_list	*intersect_list(t_intersection i1, t_intersection i2)
{
	t_intersection_list	*xs;

	xs = ft_calloc(1, sizeof(t_intersection_list));
	if (!xs)
		return (NULL);
	xs->items = ft_calloc(3, sizeof(t_intersection));
	if (!xs->items)
	{
		free(xs);
		return (NULL);
	}
	if (!i1.object && !i2.object)
		xs->count = 0;
	else
		xs->count = 2;
	xs->items[0] = i1;
	xs->items[1] = i2;
	return (xs);
}

// return the closest intersection with a positive t value, or a default
t_intersection	hit(t_intersection_list *xs)
{
	int	i;
	int	hit_index;

	hit_index = -1;
	i = 0;
	while (i < xs->count)
	{
		if (xs->items[i].t >= EPSILON && (hit_index == -1
				|| xs->items[i].t < xs->items[hit_index].t))
			hit_index = i;
		i++;
	}
	if (hit_index == -1)
		return (intersect(0, NULL, 0));
	return (xs->items[hit_index]);
}

// Joins two intersection lists into one, combining their counts and items.
// had to copy ur strjoin eshan, thanks 😋
t_intersection_list	*intersections_joined(t_intersection_list *s1,
				t_intersection_list *s2)
{
	t_intersection_list	*final;
	int					i;
	int					j;

	i = -1;
	j = -1;
	final = ft_calloc(1, sizeof(t_intersection_list));
	if (!final)
		return (NULL);
	final->count = s1->count + s2->count;
	final->items = ft_calloc(final->count, sizeof(t_intersection));
	if (!final->items)
		return (NULL);
	while (++i < s1->count)
		final->items[i] = s1->items[i];
	while (++j < s2->count)
		final->items[i++] = s2->items[j];
	free(s1->items);
	free(s1);
	free(s2->items);
	free(s2);
	sort_intersections(final);
	return (final);
}
