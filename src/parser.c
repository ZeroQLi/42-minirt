/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:40:56 by nanasser          #+#    #+#             */
/*   Updated: 2025/12/24 20:28:37 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/macros.h"

int	check_ext(char *file)
{
	int	len;

	len = ft_strlen(file) - 3;
	if (ft_strncmp(file + len, ".rt", 3) != 0)
		return (0);
	return (1);
}

int	check_element(char *line, t_data *data)
{
	data->values = ft_split(line, ' ');
	if (!data->values || !data->values[0])
	{
		free_arr(&data->values);
		return (0);
	}
	if (ft_strcmp(data->values[0], "A") == 0)
		return (parse_ambient(data->values, data));
	if (ft_strcmp(data->values[0], "C") == 0)
		return (parse_camera(data->values, data));
	if (ft_strcmp(data->values[0], "L") == 0)
		return (parse_light(data->values, data));
	if (ft_strcmp(data->values[0], "sp") == 0)
		return (parse_sphere(data->values, data));
	if (ft_strcmp(data->values[0], "pl") == 0)
		return (parse_plane(data->values, data));
	if (ft_strcmp(data->values[0], "cy") == 0)
		return (parse_cylinder(data->values, data));
	return (error_msg("Unknown identifier", 0));
}

void free_next_line(char *line, int fd)
{
	if (line)
		free(line);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static int	parse_line(t_data *d, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_or_comment(line))
		{
			if (!check_element(line, d))
			{
				free_next_line(line, fd);
				free_arr(&d->values);
				return (error_msg("wrong parser ig", 0));
			}
		}
		free(line);
		free_arr(&d->values);
		line = get_next_line(fd);
	}
	return (1); // Success!
}

// checks if the file is legit and runs parsing operation code 67
int	parse_file(t_data *data, char *file)
{
	int	fd;

	data->elements = ft_calloc(1, sizeof(t_elements));
	if (!data->elements)
		return (error_msg("MALLOC_ERROR idk how", 0));
	fd = open(file, O_RDONLY);
	if (fd < 0 || !check_ext(file))
	{
		if (fd >= 0)
			(close(fd));
		return (error_msg(INVALID_FILE, 0));
	}
	if (!parse_line(data, fd))
		return (error_msg("parsing FAILED!", 0));
	return (1);
}
