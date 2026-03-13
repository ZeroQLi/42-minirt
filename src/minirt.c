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

// Initializes the world space used to create a scene
// Moving all the values that were parsed into the actual objects
// (i aint reworking the parser again 😒)
void	new_world(t_world *w)
{
	if (w->l)
	{
		w->l->position = create_point(w->l->px, w->l->py, w->l->pz);
		w->l->intensity = color_from_rgb(w->l->cr, w->l->cg, w->l->cb);
	}
	if (w->sp)
	{
		// while (w->sp->next != NULL)
		// {
			w->sp->position = create_point(w->sp->px, w->sp->py, w->sp->pz);
			w->sp->material = create_material(w->sp);
		// }
		// w->sp = w->sp->next;
	}
	if (w->sp->next)
	{
		w->sp = w->sp->next;
		w->sp->position = create_point(w->sp->px, w->sp->py, w->sp->pz);
		w->sp->material = create_material(w->sp);
		set_transform(w->sp, scaling(0.5, 0.5, 0.5));
	}
}

static void	test_operations(t_data *data)
{
	data->canvas = create_canvas();
	render_sphere_projection(data->canvas, data->world);
	mlx_put_image_to_window(data->canvas->mlx, data->canvas->mlx_win,
			data->canvas->img, 0, 0);
	sleep(2);
	mlx_string_put(data->canvas->mlx, data->canvas->mlx_win, 25, 25, 255, "yes, I changed the sphere color. Mathew is still mathing.");
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
	// print_elements(data.elements);
	test_operations(&data);
	// test_matrix4_system();
	brain_washer(&data);
	return (0);
}
