/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:18:40 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/01 19:03:17 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	determinant_2x2(t_matrix4 m)
{
	return ((m.data[0][0] * m.data[1][1]) - (m.data[0][1] * m.data[1][0]));
}

int	minor_3x3(t_matrix3 m, int row, int col)
{
	t_matrix4	sub;
	int			det;

	sub = create_submatrix2(m, row, col);
	det = determinant_2x2(sub);
	return (det);
}
