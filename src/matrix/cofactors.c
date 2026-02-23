/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cofactors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:18:51 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/23 04:10:16 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Calculates the minor of a 3x3 matrix by creating a 2x2 submatrix
// and finding its determinant.
float	minor_3x3(t_matrix3 m, int row, int col)
{
	t_matrix4	sub;
	float		det;

	sub = create_submatrix2(m, row, col);
	det = determinant_2x2(sub);
	return (det);
}

// Calculates the cofactor of a 3x3 matrix by creating a 2x2 submatrix
// and finding its determinant.
float	cofactor_3x3(t_matrix3 m, int row, int col)
{
	float	minor;
	float	cofactor;

	minor = minor_3x3(m, row, col);
	if ((row + col) % 2 != 0)
		cofactor = -minor;
	else
		cofactor = minor;
	return (cofactor);
}

// Calculates the cofactor of a 4x4 matrix by creating a 3x3 submatrix
// and finding its determinant.
float	cofactor_4x4(t_matrix4 m, int row, int col)
{
	float	minor;
	float	cofactor;

	minor = determinant_3x3(create_submatrix3(m, row, col));
	if ((row + col) % 2 != 0)
		cofactor = -minor;
	else
		cofactor = minor;
	return (cofactor);
}
