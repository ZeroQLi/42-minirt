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

static inline t_ray	ray_for_pixel(t_camera *c, float world_x, float world_y,
	t_tuple origin)
{
	t_tuple		pixel;

	pixel = matrix4_tuple_multiply(c->inv_transform,
			create_point(world_x, world_y, -1));
	return (create_ray(origin, sub_tuples(pixel, origin)));
}

static bool	shadow_hit_list(t_intersection_list *xs, float max_t)
{
	t_intersection	h;

	if (!xs)
		return (false);
	h = hit(xs);
	free(xs->items);
	free(xs);
	return (h.object != NULL && h.t < max_t);
}

static bool	shadow_hits_world(t_world *w, t_ray shadow_ray, float dist)
{
	t_world	world;

	world.sp = w->sp;
	while (world.sp)
	{
		if (shadow_hit_list(intersect_sphere(shadow_ray, world.sp), dist))
			return (true);
		world.sp = world.sp->next;
	}
	world.pl = w->pl;
	while (world.pl)
	{
		if (shadow_hit_list(intersect_plane(shadow_ray, world.pl), dist))
			return (true);
		world.pl = world.pl->next;
	}
	world.cy = w->cy;
	while (world.cy)
	{
		if (shadow_hit_list(intersect_cylinder(shadow_ray, world.cy), dist))
			return (true);
		world.cy = world.cy->next;
	}
	return (false);
}

static t_precomp	prepare_computation(t_intersection i, t_ray ray)
{
	t_precomp	comps;

	comps.t = i.t;
	comps.object = i.object;
	comps.type = i.type;
	comps.point = position(ray, comps.t);
	comps.eyev = negate_tuple(ray.dir);
	comps.normalv = normal_at(comps.object, comps.type, comps.point);
	comps.inside = false;
	if (dot_product(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = negate_tuple(comps.normalv);
	}
	return (comps);
}

static bool	is_shadowed(t_world *w, t_precomp comp)
{
	t_tuple			to_light;
	t_ray			shadow_ray;
	float			distance;
	float			inv_distance;

	to_light = sub_tuples(w->l->light.p_light.position, comp.point);
	comp.over_point = add_tuples(comp.point, scalar_multiply(comp.normalv,
				SHADOW_BIAS));
	distance = scalar_magnitude(to_light);
	if (distance <= EPSILON)
		return (false);
	inv_distance = 1.0f / distance;
	shadow_ray = create_ray(comp.over_point,
			scalar_multiply(to_light, inv_distance));
	return (shadow_hits_world(w, shadow_ray, distance));
}

static t_material	material_at(void *object, t_type type)
{
	if (!object)
		return (create_material(0, 0, 0));
	if (type == SPHERE)
		return (((t_sphere *)object)->material);
	else if (type == PLANE)
		return (((t_plane *)object)->material);
	else if (type == CYLINDER)
		return (((t_cylinder *)object)->material);
	return (create_material(0, 0, 0));
}

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
	comp = prepare_computation(h, ray);
	free(xs->items);
	free(xs);
	return (shade_hit(w, comp));
}

static int get_time(bool stopwatch)
{
	struct timeval	start;
	struct timeval	end;

	if (stopwatch)
	{
		gettimeofday(&start, NULL);
		return (start.tv_sec);
	}
	else
	{
		gettimeofday(&end, NULL);
		return (end.tv_sec);
	}
	return (0);
}

static void	init_world_pos(t_world_render *rend, t_camera *c)
{
	rend->camera_origin = matrix4_tuple_multiply(c->inv_transform, create_point(0, 0, 0));
	rend->world_x_start = c->half_width - (0.5f * c->pixel_size);
	rend->world_y = c->half_height - (0.5f * c->pixel_size);
}

static void	draw_centered_text(t_canvas *cnv, char *text, int color)
{
	int	x;
	int	y;
	int	text_width;

	text_width = (int)ft_strlen(text) * 6;
	x = (cnv->width - text_width) / 2;
	if (x < 0)
		x = 0;
	y = (cnv->height + 13) / 2;
	mlx_string_put(cnv->mlx, cnv->mlx_win, x, y, color, text);
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
		draw_centered_text(cnv, "Rendering...", 0xFFFFFF);
	}
	r.end_time = get_time(NO);
	ft_printf("Time elapsed: %d Seconds\n", r.end_time - r.start_time);
}
