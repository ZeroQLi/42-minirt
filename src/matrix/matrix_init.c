/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:17:38 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/20 00:05:01 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Initializes a 4x4 matrix with all elements set to zero.
t_matrix4	create_matrix4(void)
{
	t_matrix4	matrix;

	ft_bzero(&matrix, sizeof(t_matrix4));
	return (matrix);
}

// Initializes a 3x3 matrix with all elements set to zero.
t_matrix3	create_matrix3(void)
{
	t_matrix3	matrix;

	ft_bzero(&matrix, sizeof(t_matrix3));
	return (matrix);
}

// Creates a 3x3 submatrix by removing the specified row and column 
// from a 4x4 matrix.
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

// Creates a 4x4 submatrix by removing the specified row and column 
// from a 3x3 matrix.
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

// Creates a 4x4 identity matrix.
// An identity matrix has 1s on the diagonal and 0s elsewhere.
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
