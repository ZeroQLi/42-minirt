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
#include "../../includes/macros.h"
#include "../../includes/shapes.h"

int	parse_normal(char *s, float *x, float *y, float *z)
{
	char	**split;

	split = ft_split(s, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		free_arr(&split);
		return (0);
	}
	*x = ft_atof(split[0]);
	*y = ft_atof(split[1]);
	*z = ft_atof(split[2]);
	free_arr(&split);
	if (*x < -1.0f || *x > 1.0f
		|| *y < -1.0f || *y > 1.0f
		|| *z < -1.0f || *z > 1.0f)
		return (0);
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
		return (0);
	}
	*r = ft_atoi(split[0]);
	*g = ft_atoi(split[1]);
	*b = ft_atoi(split[2]);
	free_arr(&split);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (0);
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
		return (0);
	}
	*x = ft_atof(split[0]);
	*y = ft_atof(split[1]);
	*z = ft_atof(split[2]);
	free_arr(&split);
	return (1);
}
