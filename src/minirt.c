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
#include "../includes/testing.h" // be sure to remove

static int	key_press(int key, t_data *data)
{
	if (key == ESC)
		brain_washer(data);
	return (0);
}

// Entry point: parses arguments, initializes canvas, and runs the main loop.
static void	test_operations(t_data *data)
{
	t_ray test;

	test = create_ray(create_point(2, 3, 4), create_vector(1, 0, 0));
	print_tuple(position(test, 2.5));
	// mlx_hook(canvas->mlx_win, 17, 0, brain_washer, data);
	// mlx_hook(canvas->mlx_win, 2, 1L << 0, key_press, data);
	// mlx_loop(canvas->mlx);
}

// le rt'ing Magie 𝓬𝓸𝓶𝓶𝓮𝓷𝓬𝓮
int	main(int ac, char **av)
{
	t_data	data;

	data = (t_data){0};
	t_tuple point;
	point = create_point(3, -2, 5, 1);
	vector = create_vector(2, 3, 4, 0);
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
	test_operations(&data);
	// test_matrix4_system();
	brain_washer(&data);
	return (0);
}
