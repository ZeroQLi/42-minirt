/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 12:11:51 by nanasser          #+#    #+#             */
/*   Updated: 2026/04/04 12:11:51 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	set_vec_normals(float *x, float *y, float *z)
{
	float	mag;
	bool	err;

	err = NO;
	mag = sqrtf((*x * *x) + (*y * *y) + (*z * *z));
	if (mag < EPSILON)
	{
		error_msg(NO, ROTATE_ERR, 2);
		*x = 0.0f;
		*y = 0.0f;
		*z = 1.0f;
		return (1);
	}
	else if (*x < -1.0f || *x > 1.0f || *y < -1.0f || *y > 1.0f
		|| *z < -1.0f || *z > 1.0f)
	{
		err = YES;
		mag = sqrtf((*x * *x) + (*y * *y) + (*z * *z));
	}
	if (err == YES)
		error_msg(NO, ROTATE_ERR, 2);
	*x /= mag;
	*y /= mag;
	*z /= mag;
	return (1);
}
