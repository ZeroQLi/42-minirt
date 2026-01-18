/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by nanasser          #+#    #+#             */
/*   Updated: 2026/01/16 00:00:00 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <stdio.h>

static void	print_ambient(t_ambient *amb)
{
	if (!amb)
		return ;
	printf(BMAGENTA "=== AMBIENT LIGHT ===" RESET "\n");
	printf("  Ratio: %.2f\n", amb->al_ratio);
	printf("  Color: RGB(%d, %d, %d)\n\n", amb->cr, amb->cg, amb->cb);
}

static void	print_camera(t_camera *cam)
{
	if (!cam)
		return ;
	printf(BCYAN "=== CAMERA ===" RESET "\n");
	printf("  Position: (%.2f, %.2f, %.2f)\n", cam->px, cam->py, cam->pz);
	printf("  Rotation: (%.2f, %.2f, %.2f)\n", cam->rx, cam->ry, cam->rz);
	printf("  FOV: %.2f\n\n", cam->fov);
}

static void	print_lights(t_light *light)
{
	int	i;

	if (!light)
		return ;
	i = 1;
	printf(BYELLOW "=== LIGHTS ===" RESET "\n");
	while (light)
	{
		printf("  Light %d:\n", i);
		printf("    Position: (%.2f, %.2f, %.2f)\n", light->px, light->py, light->pz);
		printf("    Emission: %.2f\n", light->emission);
		printf("    Color: RGB(%d, %d, %d)\n", light->cr, light->cg, light->cb);
		printf("    Fade Size: %.2f\n", light->fade_size);
		light = light->next;
		i++;
	}
	printf("\n");
}

static void	print_spheres(t_sphere *sphere)
{
	int	i;

	if (!sphere)
		return ;
	i = 1;
	printf(BGREEN "=== SPHERES ===" RESET "\n");
	while (sphere)
	{
		printf("  Sphere %d:\n", i);
		printf("    Position: (%.2f, %.2f, %.2f)\n", sphere->px, sphere->py, sphere->pz);
		printf("    Rotation: (%.2f, %.2f, %.2f)\n", sphere->rx, sphere->ry, sphere->rz);
		printf("    Diameter: %.2f\n", sphere->diameter);
		printf("    Color: RGB(%d, %d, %d)\n", sphere->cr, sphere->cg, sphere->cb);
		sphere = sphere->next;
		i++;
	}
	printf("\n");
}

static void	print_planes(t_plane *plane)
{
	int	i;

	if (!plane)
		return ;
	i = 1;
	printf(BBLUE "=== PLANES ===" RESET "\n");
	while (plane)
	{
		printf("  Plane %d:\n", i);
		printf("    Position: (%.2f, %.2f, %.2f)\n", plane->px, plane->py, plane->pz);
		printf("    Normal: (%.2f, %.2f, %.2f)\n", plane->rx, plane->ry, plane->rz);
		printf("    Size: %.2f\n", plane->size);
		printf("    Color: RGB(%d, %d, %d)\n", plane->cr, plane->cg, plane->cb);
		plane = plane->next;
		i++;
	}
	printf("\n");
}

static void	print_cylinders(t_cylinder *cylinder)
{
	int	i;

	if (!cylinder)
		return ;
	i = 1;
	printf(BRED "=== CYLINDERS ===" RESET "\n");
	while (cylinder)
	{
		printf("  Cylinder %d:\n", i);
		printf("    Position: (%.2f, %.2f, %.2f)\n", cylinder->px, cylinder->py, cylinder->pz);
		printf("    Axis: (%.2f, %.2f, %.2f)\n", cylinder->rx, cylinder->ry, cylinder->rz);
		printf("    Diameter: %.2f\n", cylinder->diameter);
		printf("    Height: %.2f\n", cylinder->height);
		printf("    Color: RGB(%d, %d, %d)\n", cylinder->cr, cylinder->cg, cylinder->cb);
		cylinder = cylinder->next;
		i++;
	}
	printf("\n");
}

void	print_elements(t_elements *elements)
{
	if (!elements)
	{
		printf(RED "Error: elements is NULL\n" RESET);
		return ;
	}
	printf(BWHITE "\n╔════════════════════════════════════╗\n");
	printf("║      SCENE ELEMENTS DEBUG          ║\n");
	printf("╚════════════════════════════════════╝\n\n" RESET);
	
	print_ambient(elements->amb);
	print_camera(elements->cam);
	print_lights(elements->l);
	print_spheres(elements->sp);
	print_planes(elements->pl);
	print_cylinders(elements->cy);
	
	printf(BWHITE "════════════════════════════════════\n\n" RESET);
}
