/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:38:21 by mtangalv          #+#    #+#             */
/*   Updated: 2026/01/25 11:43:02 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTING_H
# define TESTING_H

# include "minirt.h"

typedef struct	s_projectile
{
	t_tuple	position;
	t_tuple	velocity;
}	t_projectile;

typedef struct	s_environment
{
	t_tuple	gravity;
	t_tuple	wind;
}	t_environment;

t_projectile	tick(t_environment *env, t_projectile *proj);

#endif