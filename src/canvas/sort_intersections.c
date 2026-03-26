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

void	sort_intersections(t_intersection_list *xs)
{
	int				i;
	int				j;
	t_intersection	key;

	if (!xs || !xs->items || xs->count <= 1)
		return ;
	i = 1;
	while (i < xs->count)
	{
		key = xs->items[i];
		j = i - 1;
		while (j >= 0 && xs->items[j].t > key.t)
		{
			xs->items[j + 1] = xs->items[j];
			j--;
		}
		xs->items[j + 1] = key;
		i++;
	}
}
