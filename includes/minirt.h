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
# include <fcntl.h> // for open()

/* Colors ✨ */
/* Pls use appropriately */
# define RED   "\033[0;31m"
# define BRED  "\033[1;31m"
# define YELLOW  "\033[0;33m"
# define BYELLOW "\033[1;33m"
# define GREEN   "\033[0;32m"
# define BGREEN  "\033[1;32m"
# define BLUE    "\033[0;34m"
# define BBLUE   "\033[1;34m"
# define MAGENTA "\033[0;35m"
# define BMAGENTA "\033[1;35m"
# define CYAN    "\033[0;36m"
# define BCYAN   "\033[1;36m"
# define WHITE   "\033[0;37m"
# define BWHITE  "\033[1;37m"
# define RESET "\033[0m"

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
}	t_cylinder;

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
}	t_plane;

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
}	t_sphere;

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

typedef struct	s_elements
{
	t_ambient	*amb;
	t_camera	*cam;
	t_light		*l;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
}	t_elements;

typedef struct	s_data
{
	t_elements	*elements;
}	t_data;

//--------------------------//
//		Error & Cleanup		//
//--------------------------//
int	error_msg(char *str, int ret);

//--------------------------//
//		Parsing stuff		//
//--------------------------//
int	parse_file(t_data *data, char *file);

#endif