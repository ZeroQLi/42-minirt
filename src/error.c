/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 01:26:16 by nanasser          #+#    #+#             */
/*   Updated: 2026/01/08 01:26:16 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/macros.h"

// prints the passed error msg and returns the passed int value (ret)
int	error_msg(bool err, char *str, int fd)
{
	if (err)
		ft_putendl_fd(BRED "Error" RESET, 2);
	ft_putendl_fd(str, 2);
	return (fd);
}
