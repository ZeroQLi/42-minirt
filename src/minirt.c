/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:48:03 by nanasser          #+#    #+#             */
/*   Updated: 2025/12/23 19:48:27 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/macros.h"
#include "../includes/testing.h"

static void test_operations(void)
{
	t_matrix4 matrix;
	t_tuple data[4];

	data[0] = create_tuple(-2, -8, 3, 5);
	data[1] = create_tuple(-3, 1, 7, 3);
	data[2] = create_tuple(1, 2, -9, 6);
	data[3] = create_tuple(-6, 7, 7, -9);

	matrix = create_matrix4();
	fill_matrix4(&matrix, data);
	printf("%f, %f, %f, %f, %f\n", cofactor_4x4(matrix, 0, 0), 
		cofactor_4x4(matrix, 0, 1),
		cofactor_4x4(matrix, 0, 2),
		cofactor_4x4(matrix, 0, 3),
		determinant_4x4(matrix));
}
int	main(int ac, char **av)
{
	t_data	data;

	data = (t_data){0};
	if (ac != 2)
	{
		ft_putendl_fd(ARG_ERROR, 2);
		ft_putendl_fd("Must only have o̲n̲e̲ argument", 2);
		return (1);
	}
	if (!parse_file(&data, av[1]))
	{
		brain_washer(&data);
		return (1);
	}
	// print_elements(data.elements);

	test_operations();
	brain_washer(&data);
	ft_printf(GREEN "SUCCCESS 👍\n" RESET);
	return (0);
}
