/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 03:14:54 by nanasser          #+#    #+#             */
/*   Updated: 2026/01/15 03:14:54 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	parse_normal(char *s, float *x, float *y, float *z)
{
	char	**split;
	float	mag;

	split = ft_split(s, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		free_arr(&split);
		return (error_msg(YES, "Missing/Misconfigured Rotation values", 0));
	}
	*x = ft_atof(split[0]);
	*y = ft_atof(split[1]);
	*z = ft_atof(split[2]);
	free_arr(&split);
	if (*x < -1.0f || *x > 1.0f
		|| *y < -1.0f || *y > 1.0f
		|| *z < -1.0f || *z > 1.0f)
		return (error_msg(YES, "Rotation must be between -1 to 1", 0));
	mag = sqrtf((*x * *x) + (*y * *y) + (*z * *z));
	if (mag < EPSILON)
		return (error_msg(YES, "Misconfigured Rotation values (Must have at \
least one normalized value)", 0));
	*x /= mag;
	*y /= mag;
	*z /= mag;
	return (1);
}

int	parse_rgb(char *s, int *r, int *g, int *b)
{
	char	**split;

	if (!s)
		return (0);
	split = ft_split(s, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		free_arr(&split);
		return (error_msg(YES, "Missing/Misconfigured RGB values", 0));
	}
	else if (ft_strchr(split[0], '.') || ft_strchr(split[1], '.')
		|| ft_strchr(split[2], '.'))
		return (error_msg(YES, "RGB values must be whole", 0));
	*r = ft_atoi(split[0]);
	*g = ft_atoi(split[1]);
	*b = ft_atoi(split[2]);
	free_arr(&split);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (error_msg(YES, "RGB values must be between 0-255", 0));
	return (1);
}

int	parse_vec3(char *s, float *x, float *y, float *z)
{
	char	**split;

	if (!s)
		return (0);
	split = ft_split(s, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		free_arr(&split);
		return (error_msg(YES, "Missing/Misconfigured Position values", 0));
	}
	*x = ft_atof(split[0]);
	*y = ft_atof(split[1]);
	*z = ft_atof(split[2]);
	free_arr(&split);
	return (1);
}
