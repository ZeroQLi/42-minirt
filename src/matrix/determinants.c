/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:18:40 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/02 13:20:05 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float	determinant_2x2(t_matrix4 m)
{
	return ((m.data[0][0] * m.data[1][1]) - (m.data[0][1] * m.data[1][0]));
}

float	determinant_3x3(t_matrix3 m)
{
	float	det;
	int		col;

	col = 0;
	det = 0;
	while (col < 3)
	{
		det += m.data[0][col] * cofactor_3x3(m, 0, col);
		col++;
	}
	
	return (det);
}

float	determinant_4x4(t_matrix4 m)
{
	float	det;
	int		col;

	col = 0;
	det = 0;
	while (col < 4)
	{
		det += m.data[0][col] * cofactor_4x4(m, 0, col);
		col++;
	}
	return (det);
}