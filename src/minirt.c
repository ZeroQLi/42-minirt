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

static void	test_operations(void)
{
	t_matrix4	matrix;
	t_tuple		data[4];
	t_matrix4	res;

	data[0] = create_tuple(9, 3, 0, 9);
	data[1] = create_tuple(-5, -2, -6, -3);
	data[2] = create_tuple(-4, 9, 6, 4);
	data[3] = create_tuple(-7, 6, 6, 2);
	matrix = create_matrix4();
	matrix = create_identity();
	fill_matrix4(&matrix, data);
	res = invert_4x4(matrix);
	res = matrix_multiply(matrix, res);
	print_matrix4(res);
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
