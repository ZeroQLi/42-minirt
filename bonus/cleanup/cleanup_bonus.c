/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 03:02:43 by nanasser          #+#    #+#             */
/*   Updated: 2026/03/31 03:02:43 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_intersection_list	*free_intersections(t_intersection_list *xs)
{
	t_intersection_node	*curr;
	t_intersection_node	*next;

	if (!xs)
		return (NULL);
	curr = xs->head;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(xs);
	return (NULL);
}

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

void	free_canvas(t_canvas *canvas)
{
	if (!canvas)
		return ;
	if (canvas->mlx_win && canvas->mlx)
		mlx_clear_window(canvas->mlx, canvas->mlx_win);
	if (canvas->img)
		mlx_destroy_image(canvas->mlx, canvas->img);
	if (canvas->mlx_win && canvas->mlx)
		mlx_destroy_window(canvas->mlx, canvas->mlx_win);
	if (canvas->mlx)
	{
		mlx_destroy_display(canvas->mlx);
		free(canvas->mlx);
	}
	free(canvas);
}

int	brain_washer(t_data	*data)
{
	if (data->canvas)
		free_canvas(data->canvas);
	if (data->values)
		free_arr(&data->values);
	if (data->world)
		free_all_shapes(data->world);
	if (data->world->amb)
		free(data->world->amb);
	if (data->world->cam)
		free(data->world->cam);
	if (data->world)
		free(data->world);
	ft_printf(GREEN "SUCCCESS 👍\n" RESET);
	exit(0);
	return (0);
}
