/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:51:58 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/03 22:57:35 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef union u_tuple
{
	float	data[4];
	struct
	{
		float	x;
		float	y;
		float	z;
		float	w;
	};
}	t_tuple;

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

// tuple utils
t_tuple	create_tuple(float x, float y, float z, float w);
t_tuple	create_point(float x, float y, float z);
t_tuple	create_vector(float x, float y, float z);
int		is_point(t_tuple tuple);
int		is_equal(float a, float b);

// color utils and operations
t_color	create_color(float r, float g, float b);
t_color	multiply_colors(t_color a, float num);
t_color	add_colors(t_color a, t_color b);
t_color	sub_colors(t_color a, t_color b);
t_color	hadamard_product(t_color a, t_color b);

// tuple operations
t_tuple	add_tuples(t_tuple a, t_tuple b);
t_tuple	sub_tuples(t_tuple a, t_tuple b);
t_tuple	negate_tuple(t_tuple a);