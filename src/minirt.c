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
	t_projectile proj;
	t_environment env;
	t_canvas *canvas;
	t_color red;
	int x, y;

	red = create_color(1, 0, 0);
	canvas = create_canvas();
	proj.position = create_point(0, 1, 0);
	proj.velocity = scalar_normalize(create_vector(1, 1.8, 0));
	proj.velocity = scalar_multiply(proj.velocity, 11.25);
	env.gravity = create_vector(0, -0.1, 0);
	env.wind = create_vector(-0.01, 0, 0);

	while (proj.position.y > 0)
	{
		x = (int)proj.position.x;
		y = WIN_HEIGHT - (int)proj.position.y;
		write_pixel(canvas, x, y, red);
		proj = tick(&env, &proj); // Move AFTER drawing
	}
	mlx_put_image_to_window(canvas->mlx, canvas->mlx_win,
							canvas->img, 0, 0);
	mlx_loop(canvas->mlx);
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
