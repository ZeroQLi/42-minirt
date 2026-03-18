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

static int	key_press(int key, t_data *data)
{
	if (key == ESC)
		brain_washer(data);
	return (0);
}

t_matrix4	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward;
	t_tuple		left;
	t_tuple		true_up;
	t_matrix4	orientation;

	forward = scalar_normalize(sub_tuples(to, from));
	left = cross_product(forward, scalar_normalize(up));
	true_up = cross_product(left, forward);
	orientation = (t_matrix4){.data = {
	{left.x, left.y, left.z, 0},
	{true_up.x, true_up.y, true_up.z, 0},
	{-forward.x, -forward.y, -forward.z, 0},
	{0, 0, 0, 1}
	}};
	return (matrix_multiply(orientation,
				translation(-from.x, -from.y, -from.z)));
}

static void	test_operations(t_data *data)
{
	data->canvas = create_canvas();

	new_world(data->world);
	render(data->world->cam, data->world, data->canvas);
	printf(BGREEN "rendered\n" RESET);
	// render_sphere_projection(data->canvas, data->world);
	// mlx_put_image_to_window(data->canvas->mlx, data->canvas->mlx_win,
	// 	data->canvas->img, 0, 0);
	mlx_hook(data->canvas->mlx_win, 17, 0, brain_washer, data); // PLS DO NOT DELETE THESE ESHAN I AINT REWRITING THEM AGAIN
	mlx_hook(data->canvas->mlx_win, 2, 1L << 0, key_press, data);
	mlx_loop(data->canvas->mlx);
}

// le rt'ing Magie commence
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
	// print_elements(data.world);
	test_operations(&data);
	// test_matrix4_system();
	brain_washer(&data);
	return (0);
}
