/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:17:38 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/05 14:53:26 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_matrix4	create_matrix4(void)
{
	t_matrix4	matrix;

	ft_bzero(&matrix, sizeof(t_matrix4));
	return (matrix);
}

t_matrix3	create_matrix3(void)
{
	t_matrix3	matrix;

	ft_bzero(&matrix, sizeof(t_matrix3));
	return (matrix);
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

t_matrix4	create_identity(void)
{
	t_matrix4	identity;
	int			i;
	int			j;

	identity = create_matrix4();
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				identity.data[i][j] = 1.0;
			else
				identity.data[i][j] = 0.0;
			j++;
		}
		i++;
	}
	return (identity);
}
