/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:17:38 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/03 22:52:24 by nanasser         ###   ########.fr       */
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

int	fill_matrix4(t_matrix4 *matrix, t_tuple data[4])
{
	int	i;

	if (!matrix || !data)
		return (0);
	i = 0;
	while (i < 4)
	{
		matrix->data[i][0] = data[i].x;
		matrix->data[i][1] = data[i].y;
		matrix->data[i][2] = data[i].z;
		matrix->data[i][3] = data[i].w;
		i++;
	}
	return (1);
}

int	fill_matrix3(t_matrix3 *matrix, t_tuple data[3])
{
	int	i;

	if (!matrix || !data)
		return (0);
	i = 0;
	while (i < 3)
	{
		matrix->data[i][0] = data[i].x;
		matrix->data[i][1] = data[i].y;
		matrix->data[i][2] = data[i].z;
		i++;
	}
	return (1);
}

int	fill_matrix2(t_matrix4 *matrix, t_tuple data[2])
{
	int	i;

	if (!matrix || !data)
		return (0);
	i = 0;
	while (i < 2)
	{
		matrix->data[i][0] = data[i].x;
		matrix->data[i][1] = data[i].y;
		i++;
	}
	return (1);
}
