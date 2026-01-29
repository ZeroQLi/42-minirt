/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:18:40 by mtangalv          #+#    #+#             */
/*   Updated: 2026/01/27 22:00:22 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	determinant_2x2(t_matrix4 m)
{
	return ((m.data[0][0] * m.data[1][1]) - (m.data[0][1] * m.data[1][0]));
}

t_matrix3	create_submatrix(t_matrix4 m, int row, int col)
{
	t_matrix3	sub;
	int			i;
	int			j;
	int			sub_i;
	int			sub_j;

	sub = create_matrix3();
	sub_i = 0;
	i = 0;
	while (i < 4)
	{
		if (i == row)
			continue ;
		sub_j = 0;
		j = 0;
		while (j < 4)
		{
			if (j == col)
				continue ;
			sub.data[sub_i][sub_j++] = m.data[i][j++];
		}
		sub_i++;
		i++;
	}
	return (sub);
}
