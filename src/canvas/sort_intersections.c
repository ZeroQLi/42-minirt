/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 22:41:58 by nanasser          #+#    #+#             */
/*   Updated: 2026/03/13 22:41:58 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	swap_intersections(t_intersection *a, t_intersection *b)
{
	t_intersection	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_intersections(t_intersection_list *xs)
{
	int	i;
	int	j;

	if (!xs || !xs->items || xs->count <= 1)
		return ;
	i = 0;
	while (i < xs->count - 1)
	{
		j = 0;
		while (j < xs->count - i - 1)
		{
			if (xs->items[j].t > xs->items[j + 1].t)
				swap_intersections(&xs->items[j], &xs->items[j + 1]);
			j++;
		}
		i++;
	}
}
