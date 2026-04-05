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

// Shoots a ray from the camera through the specified pixel coordinates.
static inline t_ray	ray_for_pixel(t_camera *c, float world_x, float world_y,
	t_tuple origin)
{
	t_tuple		pixel;

	pixel = matrix4_tuple_multiply(c->inv_transform,
			create_point(world_x, world_y, -1));
	return (create_ray(origin, sub_tuples(pixel, origin)));
}

// Determines if a point is in shadow by casting a ray towards the light
// and checking for intersections with objects in the world.
static t_color	shade_hit(t_world *w, t_precomp comp)
{
	t_lighting		ctx;

	if (!w || !w->l || !comp.object)
		return (create_color(0, 0, 0));
	ctx.material = material_at(comp.object, comp.type);
	ctx.p_light = w->l->light.p_light;
	ctx.h_position = comp.point;
	ctx.eyev = comp.eyev;
	ctx.normalv = comp.normalv;
	ctx.in_shadow = is_shadowed(w, comp);
	return (lighting(&ctx, w->amb));
}

// Computes the color seen along a ray by finding the closest intersection
// and shading it accordingly.
t_color	color_at(t_world *w, t_ray ray)
{
	t_intersection_list	*xs;
	t_intersection		h;
	t_precomp			comp;

	xs = ft_calloc(1, sizeof(t_intersection_list));
	if (!xs)
		return (create_color(0, 0, 0));
	intersect_world(w, ray, xs);
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

// Stores the precomputed world position for the camera and initializes
// the starting world coordinates for ray generation.
static void	init_world_pos(t_world_render *rend, t_camera *c)
{
	rend->camera_origin = matrix4_tuple_multiply(c->inv_transform,
			create_point(0, 0, 0));
	rend->world_x_start = c->half_width - (0.5f * c->pixel_size);
	rend->world_y = c->half_height - (0.5f * c->pixel_size);
}

// Main rendering loop that iterates over each pixel, casts rays,
// and computes colors.
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
