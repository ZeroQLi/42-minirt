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

static int	rebuild_canvas_image(t_data *d)
{
	int	endian;

	if (d->canvas->img)
		mlx_destroy_image(d->canvas->mlx, d->canvas->img);
	d->canvas->img = mlx_new_image(d->canvas->mlx, d->canvas->width,
			d->canvas->height);
	if (!d->canvas->img)
		return (0);
	d->canvas->addr = mlx_get_data_addr(d->canvas->img,
			&d->canvas->bits_per_pixel, &d->canvas->line_length, &endian);
	return (1);
}

static int	on_configure(void *param)
{
	t_data				*d;
	t_xvar				*x;
	t_win_list			*w;
	XWindowAttributes	wa;

	d = (t_data *)param;
	x = (t_xvar *)d->canvas->mlx;
	w = (t_win_list *)d->canvas->mlx_win;
	if (!XGetWindowAttributes(x->display, w->window, &wa))
		return (0);
	if (wa.width <= 0 || wa.height <= 0 || (wa.width == d->canvas->width
			&& wa.height == d->canvas->height))
		return (0);
	d->canvas->width = wa.width;
	d->canvas->height = wa.height;
	d->world->cam->hsize = wa.width;
	d->world->cam->vsize = wa.height;
	if (!rebuild_canvas_image(d))
		return (0);
	camera(d->world->cam);
	render(d->world->cam, d->world, d->canvas);
	mlx_put_image_to_window(d->canvas->mlx, d->canvas->mlx_win,
		d->canvas->img, 0, 0);
	return (0);
}

// Fires up the mlx canvas and gets to the rendering magic
static inline void	play(t_data *data)
{
	data->canvas = create_canvas();
	if (!data->canvas)
		brain_washer(data);
	new_world(data->world);
	render(data->world->cam, data->world, data->canvas);
	mlx_clear_window(data->canvas->mlx, data->canvas->mlx_win);
	mlx_put_image_to_window(data->canvas->mlx, data->canvas->mlx_win,
		data->canvas->img, 0, 0);
	ft_printf(BGREEN "Done!\n" RESET);
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
	if (WIN_HEIGHT < 1 || WIN_WIDTH < 1
		|| WIN_HEIGHT > 10000 || WIN_WIDTH > 10000)
	{
		ft_putendl_fd("You thought you did something there huh", 2);
		return (1);
	}
	if (!parse_file(&data, av[1]))
	{
		brain_washer(&data);
		return (1);
	}
	play(&data);
	brain_washer(&data);
	return (0);
}
