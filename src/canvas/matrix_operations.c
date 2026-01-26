/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:22:51 by mtangalv          #+#    #+#             */
/*   Updated: 2026/01/26 21:13:28 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minirt.h"

int	matrix4_equal(t_matrix4 a, t_matrix4 b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (!is_equal(a.data[i][j], b.data[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int matrix3_equal(t_matrix3 a, t_matrix3 b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (!is_equal(a.data[i][j], b.data[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}