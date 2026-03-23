/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:22:17 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/23 20:58:11 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "matrices.h"

typedef struct s_point_light
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

typedef struct s_shape_transform
{
	t_matrix4	transform;
	t_matrix4	inv_transform;
}	t_shape_transform;

typedef struct t_lighting
{
	t_material		material;
	t_tuple			h_position;
	t_point_light	p_light;
	t_tuple			normalv;
	t_tuple			eyev;
	// values for lighting calculations. kept here to avoid norminette issues
	t_color			ambient;
	t_tuple			lightv;
	float			l_dot_n; // light dot normal
	float			r_dot_e; // reflect dot eye
	bool			in_shadow;
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
	float				height; // the max height
	float				min_height; // will be 0 for this subject
	bool				closed; // flag to close top (will be true for now)
	int					cr; // RGB range [0-255]
	int					cg;
	int					cb;
	t_shape_transform	tf;
	t_tuple				position;
	t_tuple				rotation;
	t_material			material;
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
	t_shape_transform	tf;
	t_tuple			position;
	t_tuple			rotation;
	t_material		material;
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
	t_shape_transform	tf;
	t_tuple			position; // actual position
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
	t_lighting		light;
	// float			fade_size; // will try to utilize?
	// struct s_light	*next;
}	t_light;

typedef struct s_camera
{
	float		px;
	float		py;
	float		pz;
	float		rx; // range [-1, 1]
	float		ry;
	float		rz;
	t_matrix4	transform;
	t_matrix4	inv_transform;
	t_tuple		position; // actual position
	t_tuple		rotation; // actual rotation
	float		fov; // range 0-180
	int			hsize;
	int			vsize;
	float		pixel_size;
	float		half_width;
	float		half_height;
}	t_camera;

typedef struct s_ambient
{
	float	al_ratio; // range [0.0, 1.0]
	int		cr; // RGB range [0-255]
	int		cg;
	int		cb;
	t_color	color;
}	t_ambient;

// sphere operations
void			set_transform(t_shape_transform *tf, t_matrix4 transform);

// lighting operations
t_material		create_material(int cr, int cg, int cb);
t_point_light	point_light(t_tuple position, t_color intensity);
t_color			ambient_from_world(t_lighting lighting, t_ambient *amb);
t_color			lighting(t_lighting *lighting, t_ambient *amb);

#endif