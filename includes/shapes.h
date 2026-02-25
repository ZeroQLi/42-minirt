/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:22:17 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/25 22:27:44 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "tuples.h"

typedef struct s_cylinder
{
	struct t_tuple		t_pos;
	struct t_tuple		t_rot; // range [-1, 1]
	struct s_color		t_rgb; // RGB range [0-255]
	float				px;
	float				py;
	float				pz;
	float				rx;
	float				ry;
	float				rz;
	float				diameter;
	float				height;
	float				cr;
	float				cg;
	float				cb;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_plane
{
	struct t_tuple	t_pos;
	struct t_tuple	t_rot; // range [-1, 1]
	struct s_color	t_rgb; // RGB range [0-255]
	float			px;
	float			py;
	float			pz;
	float			rx;
	float			ry;
	float			rz;
	float			size;
	float			cr;
	float			cg;
	float			cb;
	struct s_plane	*next;
}	t_plane;

typedef struct s_sphere
{
	struct t_tuple	t_pos;
	struct t_tuple	t_rot; // range [-1, 1]
	struct s_color	t_rgb; // RGB range [0-255]
	float			px;
	float			py;
	float			pz;
	float			rx;
	float			ry;
	float			rz;
	float			diameter;
	float			cr;
	float			cg;
	float			cb;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_light
{
	struct t_tuple	t_pos;
	struct t_tuple	t_rot; // range [-1, 1]
	struct s_color	t_rgb; // RGB range [0-255]
	float			px;
	float			py;
	float			pz;
	float			emission; // range [0.0, 1.0]
	float			cr; // RGB range [0-255]
	float			cg;
	float			cb;
	// float			fade_size; // will try to utilize?
	// struct s_light	*next; // if we're doing the bonus
}	t_light;

typedef struct s_camera
{
	struct t_tuple	t_pos;
	struct t_tuple	t_rot; // range [-1, 1]
	float			px;
	float			py;
	float			pz;
	float			rx;
	float			ry;
	float			rz;
	float			fov; // range 0-180
}	t_camera;

typedef struct s_ambient
{
	struct s_color	t_rgb; // RGB range [0-255]
	float			al_ratio; // range [0.0, 1.0]
	float			cr; // RGB range [0-255]
	float			cg;
	float			cb;
}	t_ambient;

#endif