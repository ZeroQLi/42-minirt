/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:24:09 by mtangalv          #+#    #+#             */
/*   Updated: 2026/01/25 11:42:24 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/testing.h"

t_projectile	tick(t_environment *env, t_projectile *proj)
{
	t_projectile	new_proj;

	new_proj.position = add_tuples(proj->position, proj->velocity);
	new_proj.velocity = add_tuples(proj->velocity,
			env->gravity);
	new_proj.velocity = add_tuples(new_proj.velocity,
			env->wind);
	return (new_proj);
}