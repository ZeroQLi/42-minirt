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

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE // for now since M_PI gives an error in vscode
# endif

# include "../libft/libft.h"

# include <fcntl.h> // for open()
# include <stdbool.h>
# include <math.h>
# include <mlx.h>
# include <sys/time.h>
# include <mlx_int.h>

# include "macros.h"
# include "shapes.h"
# include "tuples.h"
# include "matrices.h"
# include "canvas.h"

// Keybinds Definers //
# ifdef __APPLE__
#  define ESC			53
#  define UP			126
#  define DOWN			125
#  define RIGHT			124
#  define LEFT			123
#  define W				13
#  define A				0
#  define S				1
#  define D				2
#  define ON_MOUSE_DW	4
#  define SPACE			49
#  define ON_LINUX		0

# else
#  define ESC			65307
#  define MOUSE_UP		4
#  define MOUSE_DOWN	5
#  define UP			65362
#  define DOWN			65364
#  define RIGHT			65363
#  define LEFT			65361
#  define W				119
#  define A				97
#  define S				115
#  define D				100
#  define ON_MOUSE_DW	4
#  define SPACE			65
#  define ON_LINUX		1

# endif

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

typedef struct s_world_render
{
	t_ray	ray;
	t_color	color;
	t_tuple	camera_origin;
	float	world_x;
	float	world_y;
	float	world_x_start;
	int		start_time;
	int		end_time;
}	t_world_render;

typedef struct s_world
{
	t_ambient	*amb;
	t_camera	*cam;
	t_light		*l;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
}	t_world;

typedef struct s_canvas
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		width;
	int		height;
	t_color	pixels[WIN_HEIGHT][WIN_WIDTH];
}	t_canvas;

typedef struct s_data
{
	t_world		*world;
	bool		amb_exists;
	bool		cam_exists;
	bool		light_exists;
	char		**values; // to make freeing less repetitive and save lines
	t_canvas	*canvas;
}	t_data;

int					array_len(char **arr);

//--------------------------//
//		Shapes linklist		//
//--------------------------//
void				add_sphere(t_world *w, t_sphere *new);
void				add_cylinder(t_world *w, t_cylinder *new);
void				add_plane(t_world *w, t_plane *new);
void				free_spheres(t_sphere *sp);
void				free_cylinders(t_cylinder *sp);
void				free_planes(t_plane *sp);
void				free_all_shapes(t_world *w);

//--------------------------//
//		Error & Cleanup		//
//--------------------------//
int					error_msg(bool err, char *str, int fd);
char				*free_arr(char ***arr);
int					brain_washer(t_data	*data);

//--------------------------//
//		Parsing stuff		//
//--------------------------//
int					parse_file(t_data *data, char *file);
int					is_empty_or_comment(char *line);

// Shapes Parsing
int					parse_ambient(char **t, t_data *d);
int					parse_camera(char **t, t_data *d);
int					parse_light(char **t, t_data *d);
int					parse_sphere(char **t, t_data *d);
int					parse_plane(char **t, t_data *d);
int					parse_cylinder(char **t, t_data *d);

// Info Parsing
int					parse_vec3(char *s, float *x, float *y, float *z);
int					parse_normal(char *s, float *x, float *y, float *z);
int					parse_rgb(char *s, int *r, int *g, int *b);

// scalar operations
t_tuple				scalar_multiply(t_tuple a, float num);
t_tuple				scalar_divide(t_tuple a, float num);
float				scalar_magnitude(t_tuple a);
t_tuple				scalar_normalize(t_tuple a);

//vector operations
float				dot_product(t_tuple a, t_tuple b);
t_tuple				cross_product(t_tuple a, t_tuple b);

// canvas operations
t_canvas			*create_canvas(void);
void				write_pixel(t_canvas *canvas, int x, int y, t_color color);
t_color				pixel_at(t_canvas *canvas, int x, int y);
void				free_canvas(t_canvas *canvas);

// pls give these functions a family
t_color				color_from_rgb(int r, int g, int b);
void				new_world(t_world *w);
t_intersection_list	*intersect_world(t_world *w, t_ray r);
t_color				color_at(t_world *w, t_ray ray);
void				render(t_camera *c, t_world *w, t_canvas *canvas);
t_matrix4			view_transform(t_tuple from, t_tuple to, t_tuple up);
void				camera(t_camera *cam);
bool				is_shadowed(t_world *w, t_precomp comp);
int					get_time(bool stopwatch);
void				draw_centered_text(t_canvas *cnv, char *text, int color);

#endif