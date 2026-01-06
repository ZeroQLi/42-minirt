/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:04:39 by nanasser          #+#    #+#             */
/*   Updated: 2026/01/05 01:04:39 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"

typedef struct s_cylinder
{
	float	px;
	float	py;
	float	pz;
	float	rx; // range [-1, 1]
	float	ry;
	float	rz;
	float	diameter;
	float	height;
	int		cr; // RGB range [0-255]
	int		cg;
	int		cb;
};	t_cylinder;

typedef struct s_plane
{
	float	px;
	float	py;
	float	pz;
	float	rx; // range [-1, 1]
	float	ry;
	float	rz;
	float	size;
	int		cr; // RGB range [0-255]
	int		cg;
	int		cb;
};	t_plane;

typedef struct s_sphere
{
	float	px;
	float	py;
	float	pz;
	float	rx; // range [-1, 1]
	float	ry;
	float	rz;
	float	diameter;
	int		cr; // RGB range [0-255]
	int		cg;
	int		cb;
	float	fade_size; // will try to utilize?
};	t_sphere;

typedef struct	s_light
{
	float	px;
	float	py;
	float	pz;
	float	emission; // range [0.0, 1.0]
	int		cr; // RGB range [0-255]
	int		cg;
	int		cb;
}	t_light;

typedef struct	s_camera
{
	float	px;
	float	py;
	float	pz;
	float	rx; // range [-1, 1]
	float	ry;
	float	rz;
	float	fov; // range 0-180
}	t_camera;

typedef struct	s_ambient
{
	float	al_ratio; // range [0.0, 1.0]
	int		cr; // RGB range [0-255]
	int		cg;
	int		cb;
}	t_ambient;

typedef struct	s_data
{

}	t_data;

#endif