/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:25:31 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/05 14:53:43 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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
