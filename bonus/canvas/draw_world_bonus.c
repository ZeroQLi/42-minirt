/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 00:00:00 by nanasser          #+#    #+#             */
/*   Updated: 2026/03/31 00:00:00 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static inline t_ray	ray_for_pixel(t_camera *c, float world_x, float world_y,
	t_tuple origin)
{
	t_tuple		pixel;

	pixel = matrix4_tuple_multiply(c->inv_transform,
			create_point(world_x, world_y, -1));
	return (create_ray(origin, sub_tuples(pixel, origin)));
}

static t_color	shade_hit(t_world *w, t_precomp comp)
{
	t_lighting	base;
	t_lighting	ctx;
	t_light		*light;
	t_color		result;
	bool		first_light;

	base.material = material_at(comp.object, comp.type);
	base.h_position = comp.point;
	base.eyev = comp.eyev;
	base.normalv = comp.normalv;
	result = create_color(0, 0, 0);
	light = w->l;
	first_light = true;
	while (light)
	{
		ctx = base;
		ctx.p_light = light->light.p_light;
		ctx.in_shadow = is_shadowed_light(w, comp, light);
		if (!first_light)
			ctx.material.ambient = 0.0f;
		result = add_colors(result, lighting(&ctx, w->amb));
		first_light = false;
		light = light->next;
	}
	return (result);
}

t_color	color_at(t_world *w, t_ray ray)
{
	t_intersection_list	*xs;
	t_intersection		h;
	t_precomp			comp;

	xs = intersect_world(w, ray);
	if (!xs || !xs->head)
	{
		free_intersections(xs);
		return (create_color(0, 0, 0));
	}
	h = hit(xs);
	if (!h.object)
	{
		free_intersections(xs);
		return (create_color(0, 0, 0));
	}
	comp = prepare_computation(h, ray);
	free_intersections(xs);
	return (shade_hit(w, comp));
}

static void	init_world_pos(t_world_render *rend, t_camera *c)
{
	rend->camera_origin = matrix4_tuple_multiply(c->inv_transform,
			create_point(0, 0, 0));
	rend->world_x_start = c->half_width - (0.5f * c->pixel_size);
	rend->world_y = c->half_height - (0.5f * c->pixel_size);
}

void	render(t_camera *c, t_world *w, t_canvas *cnv)
{
	int				x;
	int				y;
	t_world_render	r;

	init_world_pos(&r, c);
	r.start_time = get_time(YES);
	y = -1;
	while (++y < c->vsize)
	{
		x = -1;
		r.world_x = r.world_x_start;
		while (++x < c->hsize)
		{
			r.ray = ray_for_pixel(c, r.world_x, r.world_y, r.camera_origin);
			r.color = color_at(w, r.ray);
			write_pixel(cnv, x, y, r.color);
			r.world_x -= c->pixel_size;
		}
		r.world_y -= c->pixel_size;
		mlx_put_image_to_window(cnv->mlx, cnv->mlx_win, cnv->img, 0, 0);
		draw_centered_text(cnv, "Loading level...", 0xFFFFFF);
	}
	r.end_time = get_time(NO);
	ft_printf("Time elapsed: %d Seconds\n", r.end_time - r.start_time);
}
