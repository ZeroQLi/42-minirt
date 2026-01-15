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
# include "macros.h"


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

typedef struct s_light
{
	float	px;
	float	py;
	float	pz;
	float	emission; // range [0.0, 1.0]
	int		cr; // RGB range [0-255]
	int		cg;
	int		cb;
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

typedef struct s_elements
{
	t_ambient	*amb;
	t_camera	*cam;
	t_light		*l;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
}	t_elements;

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w; // 1.0 for point, 0.0 for vector
}	t_tuple;

typedef struct s_data
{
	t_elements	*elements;
}	t_data;

int		array_len(char **arr);

//--------------------------//
//		Error & Cleanup		//
//--------------------------//
int		error_msg(char *str, int ret);
void	free_arr(char ***arr);

//--------------------------//
//		Parsing stuff		//
//--------------------------//
int		parse_file(t_data *data, char *file);
int		is_empty_or_comment(char *line);

// Shapes Parsing
int		parse_ambient(char **t, t_data *d);
int		parse_camera(char **t, t_data *d);
int		parse_light(char **t, t_data *d);
int		parse_sphere(char **t, t_data *d);
int		parse_plane(char **t, t_data *d);
int		parse_cylinder(char **t, t_data *d);

// Info Parsing
int		parse_vec3(char *s, float *x, float *y, float *z);
int		parse_normal(char *s, float *x, float *y, float *z); // checks [-1,1]
int		parse_rgb(char *s, int *r, int *g, int *b);
int		parse_ratio(char *s, float *v);

#endif