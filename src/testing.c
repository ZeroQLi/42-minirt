/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:24:09 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/05 13:18:50 by mtangalv         ###   ########.fr       */
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

void	print_tuple(t_tuple t)
{
	printf("(%f, %f, %f, %f)\n", t.x, t.y, t.z, t.w);
}

void	print_matrix4(t_matrix4 matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
			printf("%.5f ", matrix.data[i][j++]);
		printf("\n");
		i++;
	}
}

void	print_matrix3(t_matrix3 matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
			printf("%f ", matrix.data[i][j++]);
		printf("\n");
		i++;
	}
}
