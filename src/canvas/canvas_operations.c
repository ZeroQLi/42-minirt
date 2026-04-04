/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:53:39 by mtangalv          #+#    #+#             */
/*   Updated: 2026/04/04 16:48:48 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static unsigned int	color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(color.r * 255.0);
	g = (int)(color.g * 255.0);
	b = (int)(color.b * 255.0);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return ((r << 16) | (g << 8) | b);
}

// Initializes mlx, creates a blank image, and stores the ptr to the image.
// We directly place pixels through the pixel's canvas address
// instead of using mlx_pixel_put, which is very slow.
static int	setup_mlx(t_canvas *canvas)
{
	int	endian;

	canvas->mlx = mlx_init();
	if (!canvas->mlx)
		return (0);
	canvas->mlx_win = mlx_new_window(canvas->mlx, canvas->width,
			canvas->height, "Sample text");
	if (!canvas->mlx_win)
		return (0);
	canvas->img = mlx_new_image(canvas->mlx, canvas->width, canvas->height);
	canvas->addr = mlx_get_data_addr(canvas->img, &canvas->bits_per_pixel,
			&canvas->line_length, &endian);
	return (1);
}

t_canvas	*create_canvas(void)
{
	t_canvas	*canvas;

	canvas = ft_calloc(1, sizeof(t_canvas));
	if (!canvas)
		return (NULL);
	canvas->width = WIN_WIDTH;
	canvas->height = WIN_HEIGHT;
	if (!setup_mlx(canvas))
		return (NULL);
	return (canvas);
}

inline void	write_pixel(t_canvas *canvas, int x, int y, t_color color)
{
	char	*pxl;

	if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height)
	{
		if (x < WIN_WIDTH && y < WIN_HEIGHT)
			canvas->pixels[y][x] = color;
		pxl = canvas->addr + (y * canvas->line_length + x
				* (canvas->bits_per_pixel / 8));
		*(unsigned int *)pxl = color_to_int(color);
	}
}
