/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inversion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:28:17 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/05 13:19:27 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	is_invertible(t_matrix4 m)
{
	float	det;

	det = determinant_4x4(m);
	if (det == 0)
		return (0);
	return (1);
}

t_matrix4	invert_4x4(t_matrix4 m)
{
	int			i;
	int			j;
	float		cof;
	float		det;
	t_matrix4	res;

	i = 0;
	res = create_identity();
	if (!is_invertible(m))
		return (res);
	det = determinant_4x4(m);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			cof = cofactor_4x4(m, i, j);
			res.data[j][i] = cof / det;
			j++;
		}
		i++;
	}
	return (res);
}
