/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_linux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 01:36:08 by nanasser          #+#    #+#             */
/*   Updated: 2026/01/08 01:36:08 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/macros.h"

// Frees and null-terminates array, including the reference pointer.
char	*free_arr(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return (NULL);
	i = -1;
	while ((*arr)[++i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
	}
	free(*arr);
	*arr = NULL;
	return (NULL);
}

// Frees the canvas and all its components including the mlx and window ptr.
void	free_canvas(t_canvas *canvas)
{
	if (!canvas)
		return ;
	if (canvas->img)
		mlx_destroy_image(canvas->mlx, canvas->img);
	if (canvas->mlx_win)
	{
		mlx_clear_window(canvas->mlx, canvas->mlx_win);
		mlx_destroy_window(canvas->mlx, canvas->mlx_win);
	}
	if (canvas->mlx)
		mlx_destroy_display(canvas->mlx);
	free(canvas->mlx);
	free(canvas);
}

// Frees all shapes in the elements struct, then frees the struct itself.
int	brain_washer(t_data	*data)
{

	if (data->canvas)
		free_canvas(data->canvas);
	if (data->values)
		free_arr(&data->values);
	if (data->elements)
		free_all_shapes(data->elements);
	if (data->elements->amb)
		free(data->elements->amb);
	if (data->elements->cam)
		free(data->elements->cam);
	if (data->elements->l)
		free(data->elements->l);
	if (data->elements)
		free(data->elements);
	return (0);
}
