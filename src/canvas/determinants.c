/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:18:40 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/01 15:53:25 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	determinant_2x2(t_matrix4 m)
{
	return ((m.data[0][0] * m.data[1][1]) - (m.data[0][1] * m.data[1][0]));
}

t_matrix3	create_submatrix3(t_matrix4 m, int row, int col)
{
	t_matrix3	sub;
	int			i;
	int			j;
	int			sub_i;
	int			sub_j;

	sub = create_matrix3();
	sub_i = 0;
	i = -1;
	while (++i < 4)
	{
		if (i != row)
		{
			sub_j = 0;
			j = -1;
			while (++j < 4)
			{
				if (j != col)
					sub.data[sub_i][sub_j++] = m.data[i][j];
			}
			sub_i++;
		}
	}
	return (sub);
}

t_matrix4	create_submatrix2(t_matrix3 m, int row, int col)
{
	t_matrix4	sub;
	int			i;
	int			j;
	int			sub_i;
	int			sub_j;

	sub = create_matrix4();
	sub_i = 0;
	i = -1;
	while (++i < 3)
	{
		if (i != row)
		{
			sub_j = 0;
			j = -1;
			while (++j < 3)
			{
				if (j != col)
					sub.data[sub_i][sub_j++] = m.data[i][j];
			}
			sub_i++;
		}
	}
	return (sub);
}
