/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 14:03:05 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/31 03:58:11 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_intersection_node	*new_intersection_node(t_intersection value)
{
	t_intersection_node	*node;

	node = ft_calloc(1, sizeof(t_intersection_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->next = NULL;
	return (node);
}

static bool	append_intersection(t_intersection_list *xs, t_intersection value)
{
	t_intersection_node	*node;

	if (!xs)
		return (false);
	node = new_intersection_node(value);
	if (!node)
		return (false);
	if (!xs->head)
		xs->head = node;
	else
		xs->tail->next = node;
	xs->tail = node;
	return (true);
}

t_intersection_list	*create_intersections(void)
{
	t_intersection_list	*xs;

	xs = ft_calloc(1, sizeof(t_intersection_list));
	return (xs);
}

bool	intersections_push(t_intersection_list *xs, t_intersection value)
{
	if (!value.object)
		return (true);
	return (append_intersection(xs, value));
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

	xs = create_intersections();
	if (!xs)
		return (NULL);
	if (!intersections_push(xs, i1))
	{
		free_intersections(xs);
		return (NULL);
	}
	if (!intersections_push(xs, i2))
	{
		free_intersections(xs);
		return (NULL);
	}
	return (xs);
}

// return the closest intersection with a positive t value, or a default
t_intersection	hit(t_intersection_list *xs)
{
	t_intersection_node	*curr;
	t_intersection		best;
	bool				has_hit;

	if (!xs)
		return (intersect(0, NULL, 0));
	curr = xs->head;
	has_hit = false;
	best = intersect(0, NULL, 0);
	while (curr)
	{
		if (curr->value.object != NULL && curr->value.t >= EPSILON
			&& (!has_hit || curr->value.t < best.t))
		{
			best = curr->value;
			has_hit = true;
		}
		curr = curr->next;
	}
	if (!has_hit)
		return (intersect(0, NULL, 0));
	return (best);
}

// Joins two intersection lists into one, combining their counts and items.
// had to copy ur strjoin eshan, thanks 😋
t_intersection_list	*intersections_joined(t_intersection_list *s1,
				t_intersection_list *s2)
{
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	if (!s1->head)
	{
		free(s1);
		return (s2);
	}
	if (!s2->head)
	{
		free(s2);
		return (s1);
	}
	s1->tail->next = s2->head;
	s1->tail = s2->tail;
	free(s2);
	return (s1);
}

void	free_intersections(t_intersection_list *xs)
{
	t_intersection_node	*curr;
	t_intersection_node	*next;

	if (!xs)
		return ;
	curr = xs->head;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(xs);
}
