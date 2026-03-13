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

t_intersection_list	*intersect_world(t_world *w, t_ray r)
{
	t_intersection_list	*acc;
	t_intersection_list	*curr;
	t_sphere			*tmp;

	acc = intersect_list(intersect(0, NULL, 0), intersect(0, NULL, 0));
	if (!acc)
		return (NULL);
	tmp = w->sp;
	while (tmp)
	{
		curr = intersect_sphere(r, tmp);
		if (curr)
		{
			acc = intersections_joined(acc, curr);
			if (!acc)
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (acc);
}

static void	test_operations(t_data *data)
{
	// data->canvas = create_canvas();

	new_world(data->world);
	t_ray	ray = create_ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	t_intersection_list	*xs = intersect_world(data->world, ray);
	printf("Number of intersections: %d\n", xs->count);
	for (int i = 0; i < xs->count; i++)
		printf("Intersection %d: t = %f\n", i + 1, xs->items[i].t);
	free(xs->items);
	free(xs);
	// render_sphere_projection(data->canvas, data->world);
	// mlx_put_image_to_window(data->canvas->mlx, data->canvas->mlx_win,
	// 		data->canvas->img, 0, 0);
	// mlx_hook(data->canvas->mlx_win, 17, 0, brain_washer, data); // PLS DO NOT DELETE THESE ESHAN I AINT REWRITING THEM AGAIN
	// mlx_hook(data->canvas->mlx_win, 2, 1L << 0, key_press, data);
	// mlx_loop(data->canvas->mlx);
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
