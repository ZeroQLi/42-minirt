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
	return (NULL);
}

void	brain_washer(t_data	*data)
{
	if (data->values)
		free_arr(&data->values);
	if (data->elements)
		free(data->elements);
}
