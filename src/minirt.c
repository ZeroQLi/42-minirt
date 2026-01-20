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

static void test_operations(void)
{
	t_tuple a = create_vector(1,2,3);
	t_tuple b = create_vector(2,3,4);
	t_tuple res = cross_product(a, b);
	printf("Cross Product of a and b: (%f, %f, %f, %f)\n", res.x, res.y, res.z, res.w);
	t_tuple res2 = cross_product(b,a);
	printf("Cross Product of b and a: (%f, %f, %f, %f)\n", res2.x, res2.y, res2.z, res2.w);
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
