/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:22:51 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/05 17:36:35 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_matrix4	matrix_multiply(t_matrix4 a, t_matrix4 b)
{
	t_matrix4	result;
	int			i;
	int			j;

	result = create_matrix4();
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.data[i][j] = a.data[i][0] * b.data[0][j]
				+ a.data[i][1] * b.data[1][j]
				+ a.data[i][2] * b.data[2][j]
				+ a.data[i][3] * b.data[3][j];
			j++;
		}
		i++;
	}
	return (result);
}

t_tuple	matrix4_tuple_multiply(t_matrix4 m, t_tuple t)
{
	t_tuple	result;

	result = create_tuple(0, 0, 0, 0);
	result.x = m.data[0][0] * t.x + m.data[0][1] * t.y
		+ m.data[0][2] * t.z + m.data[0][3] * t.w;
	result.y = m.data[1][0] * t.x + m.data[1][1] * t.y
		+ m.data[1][2] * t.z + m.data[1][3] * t.w;
	result.z = m.data[2][0] * t.x + m.data[2][1] * t.y
		+ m.data[2][2] * t.z + m.data[2][3] * t.w;
	result.w = m.data[3][0] * t.x + m.data[3][1] * t.y
		+ m.data[3][2] * t.z + m.data[3][3] * t.w;
	return (result);
}

t_matrix4	transpose_matrix4(t_matrix4 m)
{
	t_matrix4	result;
	int			i;
	int			j;

	result = create_matrix4();
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.data[j][i] = m.data[i][j];
			j++;
		}
		i++;
	}
	return (result);
}
