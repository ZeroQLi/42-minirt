/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 06:10:07 by nanasser          #+#    #+#             */
/*   Updated: 2026/03/16 06:10:07 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_ray	ray_for_pixel(t_camera *c, float px, float py)
{
	float		xoffset;
	float		yoffset;
	float		world_x;
	float		world_y;
	//t_matrix4	invert;

	xoffset = (px + 0.5) * c->pixel_size;
	yoffset = (py + 0.5) * c->pixel_size;
	world_x = c->half_width - xoffset;
	world_y = c->half_height - yoffset;
	//invert = invert_4x4(c->transform);
	return (create_ray(matrix4_tuple_multiply(c->inv_transform, create_point(0, 0, 0)),
		scalar_normalize(sub_tuples(matrix4_tuple_multiply\
			(c->inv_transform, create_point(world_x, world_y, -1)),
			matrix4_tuple_multiply(c->inv_transform, create_point(0, 0, 0))))));
}

static t_precomp	prepare_even_more_math(t_intersection i, t_ray ray) // definitely change the name to prepare_computation REMOVE/CHANGE LATER
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

static t_color	shade_hit(t_world *w, t_precomp comp)
{
	t_lighting		ctx;
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

t_color	color_at(t_world *w, t_ray ray)
{
	t_intersection_list	*xs;
	t_intersection		h;
	t_precomp			comp;

	xs = intersect_world(w, ray);
	if (!xs || xs->count == 0)
	{
		if (xs)
		{
			free(xs->items);
			free(xs);
		}
		return (create_color(0, 0, 0));
	}
	h = hit(xs);
	if (!h.object)
	{
		free(xs->items);
		free(xs);
		return (create_color(0, 0, 0));
	}
	comp = prepare_even_more_math(h, ray);
	free(xs->items);
	free(xs);
	return (shade_hit(w, comp));
}

void	render(t_camera *c, t_world *w, t_canvas *canvas)
{
	int		x;
	int		y;
	t_ray	ray;
	t_color	color;

	y = 0;
	while (y < c->vsize)
	{
		x = 0;
		while (x < c->hsize)
		{
			ray = ray_for_pixel(c, x, y);
			color = color_at(w, ray);
			write_pixel(canvas, x, y, color);
			x++;
		}
		y++;
	}
}
