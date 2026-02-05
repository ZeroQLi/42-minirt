/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:41:28 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/05 14:28:45 by mtangalv         ###   ########.fr       */
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
t_matrix4		create_matrix4(void);
t_matrix3		create_matrix3(void);
t_matrix4		create_identity(void);
t_matrix4		transpose_matrix4(t_matrix4 m);

int				fill_matrix4(t_matrix4 *matrix, t_tuple data[4]);
int				fill_matrix3(t_matrix3 *matrix, t_tuple data[3]);
int				fill_matrix2(t_matrix4 *matrix, t_tuple data[2]);

t_matrix4		create_submatrix2(t_matrix3 m, int row, int col);
t_matrix3		create_submatrix3(t_matrix4 m, int row, int col);

// matrix operations
int				matrix4_equal(t_matrix4 a, t_matrix4 b);
int				matrix3_equal(t_matrix3 a, t_matrix3 b);
t_matrix4		matrix_multiply(t_matrix4 a, t_matrix4 b);
t_tuple			matrix4_tuple_multiply(t_matrix4 m, t_tuple t);

//cofactors and minors
float			minor_3x3(t_matrix3 m, int row, int col);
float			cofactor_3x3(t_matrix3 m, int row, int col);
float			cofactor_4x4(t_matrix4 m, int row, int col);

// determinants
float			determinant_2x2(t_matrix4 m);
float			determinant_3x3(t_matrix3 m);
float			determinant_4x4(t_matrix4 m);

// invertible
int				is_invertible(t_matrix4 m);
t_matrix4		invert_4x4(t_matrix4 m);
#endif