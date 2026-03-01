/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:22:17 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/01 05:52:05 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

typedef struct s_cylinder
{
	float				px;
	float				py;
	float				pz;
	float				rx; // range [-1, 1]
	float				ry;
	float				rz;
	float				diameter;
	float				height;
	int					cr; // RGB range [0-255]
	int					cg;
	int					cb;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_plane
{
	float			px;
	float			py;
	float			pz;
	float			rx; // range [-1, 1]
	float			ry;
	float			rz;
	float			size;
	int				cr; // RGB range [0-255]
	int				cg;
	int				cb;
	struct s_plane	*next;
}	t_plane;

typedef struct s_sphere
{
	float			px;
	float			py;
	float			pz;
	float			rx; // range [-1, 1]
	float			ry;
	float			rz;
	float			diameter;
	int				cr; // RGB range [0-255]
	int				cg;
	int				cb;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_light
{
	float			px;
	float			py;
	float			pz;
	float			emission; // range [0.0, 1.0]
	int				cr; // RGB range [0-255]
	int				cg;
	int				cb;
	// float			fade_size; // will try to utilize?
	struct s_light	*next;
}	t_light;

typedef struct s_camera
{
	float	px;
	float	py;
	float	pz;
	float	rx; // range [-1, 1]
	float	ry;
	float	rz;
	float	fov; // range 0-180
}	t_camera;

typedef struct s_ambient
{
	float	al_ratio; // range [0.0, 1.0]
	int		cr; // RGB range [0-255]
	int		cg;
	int		cb;
}	t_ambient;

#endif