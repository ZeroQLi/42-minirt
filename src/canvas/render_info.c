/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 16:55:19 by nanasser          #+#    #+#             */
/*   Updated: 2026/03/28 16:55:19 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	get_time(bool stopwatch)
{
	struct timeval	start;
	struct timeval	end;

	if (stopwatch)
	{
		gettimeofday(&start, NULL);
		return (start.tv_sec);
	}
	else
	{
		gettimeofday(&end, NULL);
		return (end.tv_sec);
	}
	return (0);
}

void	draw_centered_text(t_canvas *cnv, char *text, int color)
{
	int	x;
	int	y;
	int	text_width;

	text_width = (int)ft_strlen(text) * 6;
	x = (cnv->width - text_width) / 2;
	if (x < 0)
		x = 0;
	y = (cnv->height + 13) / 2;
	mlx_string_put(cnv->mlx, cnv->mlx_win, x, y, color, text);
}
