/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 16:42:21 by nanasser          #+#    #+#             */
/*   Updated: 2026/03/28 16:42:21 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool	sphere_shadow_hit(t_ray ray, t_sphere *sphere, float max_t)
{
	t_tuple	sphere_to_ray;
	float	a;
	float	b;
	float	disc;
	float	t;

	ray = transform_ray(ray, sphere->tf.inv_transform);
	sphere_to_ray = sub_tuples(ray.origin, create_point(0, 0, 0));
	a = dot_product(ray.dir, ray.dir);
	b = 2.f * dot_product(ray.dir, sphere_to_ray);
	disc = (b * b) - (4.f * a
			* (dot_product(sphere_to_ray, sphere_to_ray) - 1.f));
	if (disc < 0)
		return (false);
	t = (-b - sqrtf(disc)) / (2.f * a);
	if (t >= EPSILON && t < max_t)
		return (true);
	t = (-b + sqrtf(disc)) / (2.f * a);
	return (t >= EPSILON && t < max_t);
}

static bool	plane_shadow_hit(t_ray ray, t_plane *plane, float max_t)
{
	float	t;

	ray = transform_ray(ray, plane->tf.inv_transform);
	if (fabsf(ray.dir.y) < EPSILON)
		return (false);
	t = -ray.origin.y / ray.dir.y;
	return (t >= EPSILON && t < max_t);
}

static inline bool	check_caps(t_ray ray, float t)
{
	float	x;
	float	z;

	x = ray.origin.x + t * ray.dir.x;
	z = ray.origin.z + t * ray.dir.z;
	return (((x * x) + (z * z)) <= 1.0f);
}

static bool	cylinder_shadow_hit(t_ray ray, t_cylinder *cylinder, float max_t)
{
	t_tuple	cylinder_to_ray;
	float	a;
	float	b;
	float	disc;
	float	t;
	float	y;

	ray = transform_ray(ray, cylinder->tf.inv_transform);
	a = (ray.dir.x * ray.dir.x) + (ray.dir.z * ray.dir.z);
	if (fabsf(a) >= EPSILON)
	{
		cylinder_to_ray = sub_tuples(ray.origin, create_point(0, 0, 0));
		b = 2.f * ((ray.dir.x * cylinder_to_ray.x)
				+ (ray.dir.z * cylinder_to_ray.z));
		disc = (b * b) - (4.f * a * ((cylinder_to_ray.x * cylinder_to_ray.x)
					+ (cylinder_to_ray.z * cylinder_to_ray.z) - 1.f));
		if (disc >= 0)
		{
			t = (-b - sqrtf(disc)) / (2.f * a);
			y = ray.origin.y + t * ray.dir.y;
			if (t >= EPSILON && t < max_t
				&& y >= -cylinder->height && y <= cylinder->height)
				return (true);
			t = (-b + sqrtf(disc)) / (2.f * a);
			y = ray.origin.y + t * ray.dir.y;
			if (t >= EPSILON && t < max_t
				&& y >= -cylinder->height && y <= cylinder->height)
				return (true);
		}
	}
	if (cylinder->closed == NO || fabsf(ray.dir.y) < EPSILON)
		return (false);
	t = (-cylinder->height - ray.origin.y) / ray.dir.y;
	if (t >= EPSILON && t < max_t && check_caps(ray, t))
		return (true);
	t = (cylinder->height - ray.origin.y) / ray.dir.y;
	return (t >= EPSILON && t < max_t && check_caps(ray, t));
}

static bool	shadow_hits_world(t_world *w, t_ray shadow_ray, float dist)
{
	t_world	world;

	world.sp = w->sp;
	while (world.sp)
	{
		if (sphere_shadow_hit(shadow_ray, world.sp, dist))
			return (true);
		world.sp = world.sp->next;
	}
	world.pl = w->pl;
	while (world.pl)
	{
		if (plane_shadow_hit(shadow_ray, world.pl, dist))
			return (true);
		world.pl = world.pl->next;
	}
	world.cy = w->cy;
	while (world.cy)
	{
		if (cylinder_shadow_hit(shadow_ray, world.cy, dist))
			return (true);
		world.cy = world.cy->next;
	}
	return (false);
}

t_precomp	prepare_computation(t_intersection i, t_ray ray)
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

bool	is_shadowed(t_world *w, t_precomp comp)
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

t_material	material_at(void *object, t_type type)
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

/*..............................................................................
................................................................................
.........................-=*****####****+=-.....................................
.......................-*@@@@@@@@@@@%%########+=:...............................
..........................:#@@@@@@@@@@@@@@%#######*=............................
.............................*@@@@@@@@@@@@@@@%#######*=.........................
...............................%@@@@@@@@@@@@@@@@%#######*.......................
........-*:.....................=@@@@@@@@@@@@@@@@@%#######*:....................
.......:###=.....................:@@@@@@@@@@@@@@@@@@%#######*:...........-#@@...
.......*%###*=....................:@@@@@@@@@@@@@@@@@@@########+......:*@@@@@%...
......:%@######*-..................=@@@@@@@@@@@@@@@@@@@@########=.:*@@@@@@@@=...
......-@@@########*+=:.............-%@@@@@@@@@@@@@@@@@@@@#######%@@@@@@@@@@%:...
......-@@@@%#######################%@@@@@@@@@@@@@@@@@@@@@@%###@@@@@@@@@@@@@=....
......-@@@@@@%####################%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+.....
......:%@@@@@@@%#################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*......
.......*@@@@@@@@@@@###########%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#.......
........%@@@@@@@@@@@@@%####%@@@@@@@@@@@@@@@@@@%####%@@@@@@@@@@@@@@@@@@@@:.......
.........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%#######@@@@@@@@@@@@@@@@@@#........
.........:%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%####+:. .-%@@@@@@@@@@@@@%##-.......
...........*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@###-.       *@@@@@@@@@@@####=.......
............:#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##:.         :@@@@@@@@@%####=.......
...*:..........=@@@@@@@@@@@@@@@@@@@@@@@@@@@%#:            =@@@@@@@@@####:.......
...+@#=:..........=%@@@@@@@@@@@@@@@@@@@@@@@%*.       :#@* .+@@@@@@@@@###........
...-@@@###**=-:::::::=%%##@@@@@@@@@@@@@@@@@@+.      -@@@*   #@@@@@@@@##-........
...:#@@@%################@@@@@@@@@@@@@@@@@@@#.     .@@@%:   :@@@@@@@@%+.........
....=@@@@@%############%@@@@@@@@@@@@@@@@@@@@@:    .@@@@:    .*@@@@@@@#:.........
.....+@@@@@@@%######%@@@@@@@@@@@@@@@@@@@@@@@@@.   *@@+.     .+@@@@@@@:..........
......=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%:. ...       .+@@@@@%............
.......:%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@=.         .+@@@@*.............
.........-%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%*==-:...+@@#:..............
...........=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+................
.............=%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-.............
................*@@@@@@@@@@@@@@@@@@@@@%@@@@@@@@@@@@@@@@@@@@@@@@@@=@@@#+-:.......
..................:=*%@@@@@@@@@@#+-:....:-+#@@@@@@@@@@@@@@@@@@#=...+%@%*:.......
.................................................:-++****+-.....................
................................................................................
..............................................................................*/