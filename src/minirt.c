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

static void	test_operations(t_data *data)
{
	(void)data;
	t_canvas *canvas = create_canvas();

	render_sphere_projection(canvas);
	mlx_put_image_to_window(canvas->mlx, canvas->mlx_win, canvas->img, 0, 0);
	mlx_loop(canvas->mlx);
}

// le rt'ing Magie commence
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
