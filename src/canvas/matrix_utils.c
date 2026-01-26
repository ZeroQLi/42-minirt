/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:25:31 by mtangalv          #+#    #+#             */
/*   Updated: 2026/01/26 22:38:36 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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

t_matrix4	transpose_matrix4(t_matrix4 m)
{
	t_matrix4	result;
	int			i;
	int			j;

	result = create_matrix4();
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.data[j][i] = m.data[i][j];
			j++;
		}
		i++;
	}
	return (result);
}