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

// Joins two intersection lists into one, combining their counts and items.
// had to copy ur strjoin eshan, thanks 😋
t_intersection_list	*intersections_joined(t_intersection_list *s1, t_intersection_list *s2)
{
	t_intersection_list	*final;
	int					i;
	int					j;

	i = -1;
	j = -1;
	final = ft_calloc(1, sizeof(t_intersection_list));
	if (!final)
		return (NULL);
	final->count = s1->count + s2->count;
	final->items = ft_calloc(final->count, sizeof(t_intersection));
	if (!final->items)
		return (NULL);
	while (++i < s1->count)
		final->items[i] = s1->items[i];
	while (++j < s2->count)
		final->items[i++] = s2->items[j];
	free(s1->items);
	free(s1);
	free(s2->items);
	free(s2);
	return (final);
}

// Entry point: parses arguments, initializes canvas, and runs the main loop.
static void render_sphere_projection(t_canvas *canvas)
{
	t_tuple ray_origin;
	float wall_z;
	float wall_width;
	float wall_height;
	float pixel_size_x;
	float pixel_size_y;
	float half_width;
	float half_height;
	t_color red;
	t_sphere *sphere;
	t_intersection_list *xs;
	t_intersection h;
	t_tuple position;
	t_ray ray;
	float world_x;
	float world_y;
	int x;
	int y;

	ray_origin = create_point(0, 0, -5);
	wall_z = 10.0f;
	wall_height = 7.0f;
	wall_width = wall_height * ((float)WIN_WIDTH / (float)WIN_HEIGHT);
	pixel_size_x = wall_width / WIN_WIDTH;
	pixel_size_y = wall_height / WIN_HEIGHT;
	half_width = wall_width / 2.0f;
	half_height = wall_height / 2.0f;
	red = create_color(1, 0, 0);
	sphere = create_sphere();
	if (!sphere)
		return;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		world_y = half_height - pixel_size_y * (y + 0.5f);
		x = 0;
		while (x < WIN_WIDTH)
		{
			world_x = -half_width + pixel_size_x * (x + 0.5f);
			position = create_point(world_x, world_y, wall_z);
			ray = create_ray(ray_origin, sub_tuples(position, ray_origin));
			xs = intersect_sphere(ray, sphere);
			if (xs)
			{
				h = hit(xs);
				if (h.object)
					write_pixel(canvas, x, y, red);
				free(xs->items);
				free(xs);
			}
			x++;
		}
		y++;
	}
	free(sphere);
}

static void	test_operations(t_data *data)
{
	t_canvas	*canvas;

	(void)data;
	canvas = create_canvas();
	if (!canvas)
		return ;
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
