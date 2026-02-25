/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:31:44 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/25 20:59:16 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include "tuples.h" 

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	dir;
}	t_ray;

t_ray	create_ray(t_tuple origin, t_tuple direction);
t_tuple	position(t_ray ray, float t);

#endif