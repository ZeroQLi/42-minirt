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
#include "../includes/testing.h" // be sure to remove

// static int	key_press(int key, t_data *data)
// {
// 	if (key == ESC)
// 		brain_washer(data);
// 	return (0);
// }

// Entry point: parses arguments, initializes canvas, and runs the main loop.
static void	test_operations(t_data *data)
{
	t_ray r;
	t_sphere *s;
	float *xs;

	(void)data;
	// Test: A ray intersects a sphere at a tangent
	r = create_ray(create_point(0, 0, 5), create_vector(0, 0, 1));
	s = create_sphere();
	xs = intersect_sphere(r, s);

	printf("Test: Ray intersects sphere at tangent\n");
	printf("%f\n%f\n%f\n", xs[0], xs[1], xs[2]);

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
	t_tuple vector;
	point = create_point(3, -2, 5);
	vector = create_vector(2, 3, 4);
	(void)point;
	(void)vector;
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
