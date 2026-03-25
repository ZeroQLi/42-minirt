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

static t_ray	ray_for_pixel(t_camera *c, float world_x, float world_y,
	t_tuple origin)
{
	t_tuple		pixel;

	pixel = matrix4_tuple_multiply(c->inv_transform,
			create_point(world_x, world_y, -1));
	return (create_ray(origin, scalar_normalize(sub_tuples(pixel, origin))));
}

static bool	shadow_hit_in_list(t_intersection_list *xs, float max_t)
{
	t_intersection	h;

	if (!xs)
		return (false);
	h = hit(xs);
	free(xs->items);
	free(xs);
	return (h.object != NULL && h.t < max_t);
}

static bool	shadow_hits_world(t_world *w, t_ray shadow_ray, float distance)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	sp = w->sp;
	while (sp)
	{
		if (shadow_hit_in_list(intersect_sphere(shadow_ray, sp), distance))
			return (true);
		sp = sp->next;
	}
	pl = w->pl;
	while (pl)
	{
		if (shadow_hit_in_list(intersect_plane(shadow_ray, pl), distance))
			return (true);
		pl = pl->next;
	}
	cy = w->cy;
	while (cy)
	{
		if (shadow_hit_in_list(intersect_cylinder(shadow_ray, cy), distance))
			return (true);
		cy = cy->next;
	}
	return (false);
}

static t_precomp	prepare_even_more_math(t_intersection i, t_ray ray) // definitely change the name to prepare_computation REMOVE/CHANGE LATER
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
	comp.over_point = add_tuples(comp.point, scalar_multiply(comp.normalv, SHADOW_BIAS));
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
	t_tuple	camera_origin;
	float	world_x;
	float	world_y;
	float	world_x_start;
	struct timeval	start, end;

	y = 0;
	camera_origin = matrix4_tuple_multiply(c->inv_transform, create_point(0, 0, 0));
	world_x_start = c->half_width - (0.5f * c->pixel_size);
	world_y = c->half_height - (0.5f * c->pixel_size);
	
	gettimeofday(&start, NULL);
	while (y < c->vsize)
	{
		x = 0;
		world_x = world_x_start;
		while (x < c->hsize)
		{
			ray = ray_for_pixel(c, world_x, world_y, camera_origin);
			color = color_at(w, ray);
			write_pixel(canvas, x, y, color);
			world_x -= c->pixel_size;
			x++;
		}
		world_y -= c->pixel_size;
		y++;
		mlx_put_image_to_window(canvas->mlx, canvas->mlx_win, canvas->img, 0, 0);
		mlx_string_put(canvas->mlx, canvas->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2, 0xFFFFFF, "Rendering...");
	}
	gettimeofday(&end, NULL);
	ft_printf("Time elapsed: %d Seconds\n", end.tv_sec - start.tv_sec);
	mlx_clear_window(canvas->mlx, canvas->mlx_win);
	mlx_put_image_to_window(canvas->mlx, canvas->mlx_win, canvas->img, 0, 0);
}
