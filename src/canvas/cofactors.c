/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cofactors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:18:51 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/02 13:19:19 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float	minor_3x3(t_matrix3 m, int row, int col)
{
	t_matrix4	sub;
	float		det;

	sub = create_submatrix2(m, row, col);
	det = determinant_2x2(sub);
	return (det);
}

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