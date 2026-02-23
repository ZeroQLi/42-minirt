/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:31:44 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/23 16:30:14 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

typedef struct s_ray {
	t_tuple	origin;
	t_tuple	dir;
}	t_ray;

t_ray	create_ray(t_tuple origin, t_tuple direction);
t_tuple	position(t_ray ray, float t);

#endif