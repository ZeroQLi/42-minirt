/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:06:31 by nanasser          #+#    #+#             */
/*   Updated: 2026/01/08 21:06:31 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/macros.h"

int	is_empty_or_comment(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] >= 9 && line[i] <= 13) || (line[i] == 32)
		i++;
	if (line[i] == '\0' || line[i] == '#')
		return (1);
	return (0);
}

int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}
