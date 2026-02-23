/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:18:40 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/23 04:14:07 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Calculates the determinant of a 2x2 matrix.
float	determinant_2x2(t_matrix4 m)
{
	return ((m.data[0][0] * m.data[1][1]) - (m.data[0][1] * m.data[1][0]));
}

// Calculates the determinant of a 3x3 matrix using cofactor expansion
// along the first row.
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

// Calculates the determinant of a 4x4 matrix using cofactor expansion
// along the first row.
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
