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

t_precomp	prepare_even_more_math(t_intersection i, t_ray ray) // definitely change the name to prepare_computation REMOVE/CHANGE LATER
{
	t_precomp	comps;

	comps.t = i.t;
	comps.object = i.object;
	comps.type = i.type;
	comps.point = position(ray, comps.t);
	comps.eyev = negate_tuple(ray.dir);
	comps.normalv = normal_at(comps.object, comps.point);
	comps.inside = false;
	if (dot_product(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = negate_tuple(comps.normalv);
	}
	return (comps);
}

t_color	shade_hit(t_world *w, t_precomp comp)
{
	t_lighting	ctx;
	t_sphere		*sphere;

	if (!w || !w->l || !comp.object)
		return (create_color(0, 0, 0));
	sphere = (t_sphere *)comp.object;
	ctx.material = sphere->material;
	ctx.p_light = w->l->light.p_light;
	ctx.h_position = comp.point;
	ctx.eyev = comp.eyev;
	ctx.normalv = comp.normalv;
	return (lighting(&ctx));
}

static void	test_operations(t_data *data)
{
	// data->canvas = create_canvas();
	t_precomp	precomp;

	new_world(data->world);
	t_ray	ray = create_ray(create_point(0, 0, 0), create_vector(0, 0, 1));
	t_intersection	i = intersect(0.5, data->world->sp->next, SPHERE);
	precomp = prepare_even_more_math(i, ray);
	t_color		c = shade_hit(data->world, precomp);
	printf("Shading at hit: R=%.2f, G=%.2f, B=%.2f\n", c.r, c.g, c.b);
	// (void)precomp;
	// free(xs->items);
	// free(xs);
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
