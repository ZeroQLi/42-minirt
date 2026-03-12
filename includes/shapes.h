/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:22:17 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/12 21:49:59 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "matrices.h"

typedef struct point_light
{
	t_tuple	position;
	t_color	intensity;
}	t_point_light;

typedef struct s_material
{
    t_color	color;
    float	ambient;
    float	diffuse;
    float	specular;
    float	shininess;
}	t_material;

typedef struct t_lighting
{
	t_material		material;
	t_tuple			position;
	t_point_light	light;
	t_tuple			normalv;
	t_tuple			eyev;
	// values for lighting calculations. kept here to avoid norminette issues in the lighting function
	t_color			ambient;
	t_tuple			lightv;
	float			l_dot_n; // light dot normal
	float			r_dot_e; // reflect dot eye
	t_color			diffuse;
	t_color			specular;
	t_color			result;
}	t_lighting;

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
	t_matrix4		transform; //store the transformation matrix for the sphere
	t_material		material; // store the material properties for the sphere
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

// sphere operations
t_sphere		*create_sphere(void);
void			set_transform(t_sphere *sphere, t_matrix4 transform);

// lighting operations
t_material		create_material(void);
t_point_light	point_light(t_tuple position, t_color intensity);
t_color			lighting(t_lighting *lighting);
#endif