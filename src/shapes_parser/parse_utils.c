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

int	ft_isdigit_str(const char *str)
{
	int		i;
	bool	is_dec;

	i = 0;
	is_dec = NO;
	if (str[i] == '-')
		i++;
	if (ft_strlen(&str[i]) > 10)
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) && str[i + 1] == '.')
		{
			i++;
			if (!ft_isdigit(str[i + 1]) || is_dec == YES)
				return (0);
			is_dec = YES;
		}
		else if (!ft_isdigit(str[i]) && str[i] != '\n' && str[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_isdigit_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (!ft_isdigit_str(arr[i]))
		{
			free_arr(&arr);
			return (0);
		}
		i++;
	}
	return (1);
}

int	parse_normal(char *s, float *x, float *y, float *z)
{
	char	**split;

	split = ft_split(s, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		free_arr(&split);
		return (error_msg(YES, "Missing/Misconfigured Rotation values", 0));
	}
	if (!ft_isdigit_arr(split))
		return (error_msg(YES, "Rotation values must be a valid number", 0));
	*x = ft_atof(split[0]);
	*y = ft_atof(split[1]);
	*z = ft_atof(split[2]);
	free_arr(&split);
	return (set_vec_normals(x, y, z));
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
	{
		free_arr(&split);
		return (error_msg(YES, "RGB values must be whole", 0));
	}
	if (!ft_isdigit_arr(split))
		return (error_msg(YES, "RGB values must be a valid number", 0));
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
	if (!ft_isdigit_arr(split))
		return (error_msg(YES, "Position values must be a valid number", 0));
	*x = ft_atof(split[0]);
	*y = ft_atof(split[1]);
	*z = ft_atof(split[2]);
	free_arr(&split);
	return (1);
}
