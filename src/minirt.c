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
	t_canvas	*canvas;
	t_tuple		origin;
	t_matrix4		hour;
	t_tuple			twelve;
	t_tuple			point;

	canvas = create_canvas();
	mlx_put_image_to_window(canvas->mlx, canvas->mlx_win, canvas->img, 0, 0);
	origin = create_point(WIN_WIDTH / 2, WIN_HEIGHT / 2, 3);
	twelve = create_point(0, WIN_HEIGHT / 3, 1);
	for (int i = 0; i < 64; i++)
	{
		point = origin;
		hour = rotation_z(i * (M_PI / 32));
		point = matrix4_tuple_multiply(hour, twelve);
		point.x += origin.x;
		point.y += origin.y;
		write_pixel(canvas, point.x, point.y, create_color(0, 255, 255));
	}
	// write_pixel(canvas, origin.x, origin.y, create_color(255, 0, 0));
	// mlx_hook(canvas->mlx_win, 17, 0, brain_washer, canvas);
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
	// test_operations();
	test_matrix4_system();
	brain_washer(&data);
	ft_printf(GREEN "SUCCCESS 👍\n" RESET);
	return (0);
}
