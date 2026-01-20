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
# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include "macros.h"

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
	float			fade_size; // will try to utilize?
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
	float	x;
	float	y;
	float	z;
	float	w; // 1.0 for point, 0.0 for vector
}	t_tuple;

typedef struct s_data
{
	t_elements	*elements;
	bool		amb_exists;
	bool		cam_exists;
	bool		light_exists;
	char		**values; // to make freeing less repetitive and save lines
}	t_data;

int		array_len(char **arr);

//--------------------------//
//		Shapes linklist		//
//--------------------------//
void	add_sphere(t_elements *e, t_sphere *new);
void	add_cylinder(t_elements *e, t_cylinder *new);
void	add_plane(t_elements *e, t_plane *new);
void	free_spheres(t_sphere *sp);
void	free_cylinders(t_cylinder *sp);
void	free_planes(t_plane *sp);
void	free_all_shapes(t_elements *e);

//--------------------------//
//		Error & Cleanup		//
//--------------------------//
int		error_msg(bool err, char *str, int ret);
char	*free_arr(char ***arr);
void	brain_washer(t_data	*data);

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

// tuple utils
t_tuple	create_tuple(double x, double y, double z, double w);
t_tuple	create_point(double x, double y, double z);
t_tuple	create_vector(double x, double y, double z);
int		is_point(t_tuple tuple);
int		is_equal(float a, float b);

// tuple operations
t_tuple	add_tuples(t_tuple a, t_tuple b);
t_tuple sub_tuples(t_tuple a, t_tuple b);
t_tuple	negate_tuple(t_tuple a);

// scalar operations
t_tuple	scalar_multiply(t_tuple a, float num);
t_tuple	scalar_divide(t_tuple a, float num);
float	scalar_magnitude(t_tuple a);
t_tuple	scalar_normalize(t_tuple a);

//vector operations
float	dot_product(t_tuple a, t_tuple b);
t_tuple	cross_product(t_tuple a, t_tuple b);

// value table print tester
void	print_elements(t_elements *elements);

#endif