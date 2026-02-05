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
	t_matrix4	m;
	t_tuple		t;

	m = rotation_x(M_PI / 4);
	t = create_point(0, 1, 0);
	t = matrix4_tuple_multiply(m, t);
	print_tuple(t);

	m = rotation_y(M_PI / 4);
	t = create_point(0, 0, 1);
	t = matrix4_tuple_multiply(m, t);
	print_tuple(t);

	m = rotation_z(M_PI / 4);
	t = create_point(0, 1, 0);
	t = matrix4_tuple_multiply(m, t);
	print_tuple(t);
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
