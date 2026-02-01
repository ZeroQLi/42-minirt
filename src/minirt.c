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
	t_matrix4 a;

	a = create_matrix4();
	t_tuple nums[4];

	nums[0] = create_tuple(-6, 1, 1, 6);
	nums[1] = create_tuple(-8, 5, 8, 6);
	nums[2] = create_tuple(-1, 0, 8, 2);
	nums[3] = create_tuple(-7, 1, -1, 1);
	fill_matrix4(&a, nums);
	print_matrix4(a);
	printf("\n");
	t_matrix3 sub = create_submatrix3(a, 2, 1);
	print_matrix3(sub);
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
