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

static int	key_press(int key, t_data *data)
{
	if (key == ESC)
		brain_washer(data);
	return (0);
}

t_color	color_from_rgb(int r, int g, int b)
{
	return (create_color(r / 255.0f, g / 255.0f, b / 255.0f));
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

static int on_configure(void *param)
{
    t_data *d = (t_data *)param;
    t_xvar *x = (t_xvar *)d->canvas->mlx;
    t_win_list *w = (t_win_list *)d->canvas->mlx_win;
    XWindowAttributes wa;

    if (!XGetWindowAttributes(x->display, w->window, &wa))
        return (0);
    if (wa.width == d->canvas->width && wa.height == d->canvas->height)
        return (0);
    d->canvas->width = wa.width;
    d->canvas->height = wa.height;
    d->world->cam->hsize = wa.width;
    d->world->cam->vsize = wa.height;
	mlx_clear_window(d->canvas->mlx, d->canvas->mlx_win);
    render(d->world->cam, d->world, d->canvas);
	mlx_clear_window(d->canvas->mlx, d->canvas->mlx_win);
	mlx_put_image_to_window(d->canvas->mlx, d->canvas->mlx_win,
			d->canvas->img, 0, 0);
    return (0);
}

static inline void	test_operations(t_data *data)
{
	data->canvas = create_canvas();
	if (!data->canvas)
		brain_washer(data);
	new_world(data->world);
	render(data->world->cam, data->world, data->canvas);
	mlx_clear_window(data->canvas->mlx, data->canvas->mlx_win);
	mlx_put_image_to_window(data->canvas->mlx, data->canvas->mlx_win,
			data->canvas->img, 0, 0);
	printf(BGREEN "rendered\n" RESET);
	mlx_hook(data->canvas->mlx_win, 22, 1L << 17, on_configure, data);
	mlx_hook(data->canvas->mlx_win, 17, 0, brain_washer, data);
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
	if (WIN_HEIGHT < 1 || WIN_WIDTH < 1)
	{
		ft_putendl_fd("You thought you did something there huh", 2);
		return (1);
	}
	if (!parse_file(&data, av[1]))
	{
		brain_washer(&data);
		return (1);
	}
	test_operations(&data); // rename this
	brain_washer(&data);
	return (0);
}
