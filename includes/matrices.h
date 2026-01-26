/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:41:28 by mtangalv          #+#    #+#             */
/*   Updated: 2026/01/26 20:58:55 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRICES_H
# define MATRICES_H

# include "minirt.h"

typedef union u_matrix4
{
	float	data[4][4];
	struct 
	{
		t_tuple	r0;
		t_tuple	r1;
		t_tuple	r2;
		t_tuple	r3;
	};
}	t_matrix4;

typedef union u_matrix3
{
	float	data[3][3];
	struct
	{
		t_tuple	r0;
		t_tuple	r1;
		t_tuple	r2;
	};
}	t_matrix3;

// matrix utils
t_matrix4	create_matrix4(void);
t_matrix3	create_matrix3(void);

int			fill_matrix4(t_matrix4 *matrix, t_tuple data[4]);
int			fill_matrix3(t_matrix3 *matrix, t_tuple data[3]);
int			fill_matrix2(t_matrix4 *matrix, t_tuple data[2]);

// matrix operations
int			matrix4_equal(t_matrix4 a, t_matrix4 b);

#endif