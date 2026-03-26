/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:53:39 by mtangalv          #+#    #+#             */
/*   Updated: 2026/03/26 19:22:32 by nanasser         ###   ########.fr       */
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
	setup_mlx(canvas); // should return and free on failure, do fix
	return (canvas);
}

void	write_pixel(t_canvas *canvas, int x, int y, t_color color)
{
	char	*pxl;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		canvas->pixels[y][x] = color;
		pxl = canvas->addr + (y * canvas->line_length + x
				* (canvas->bits_per_pixel / 8));
		*(unsigned int *)pxl = color_to_int(color);
	}
}

t_color	pixel_at(t_canvas *canvas, int x, int y)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		return (canvas->pixels[y][x]);
	return ((t_color){0, 0, 0});
}
