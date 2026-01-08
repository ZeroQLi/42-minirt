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

int	parse_line(char *line, t_data *data)
{
	char	**values;

	values = ft_split(line, ' ');
	if (!values || !values[0])
	{
		free_arr(values);
		return (0);
	}
	if (ft_strcmp(values[0], "A") == 0)
		return (parse_ambient(values, data));
	if (ft_strcmp(values[0], "C") == 0)
		return (parse_camera(values, data));
	if (ft_strcmp(values[0], "L") == 0)
		return (parse_light(values, data));
	if (ft_strcmp(values[0], "sp") == 0)
		return (parse_sphere(values, data));
	if (ft_strcmp(values[0], "pl") == 0)
		return (parse_plane(values, data));
	if (ft_strcmp(values[0], "cy") == 0)
		return (parse_cylinder(values, data));
	free_arr(values);
	return (error_msg("Unknown identifier", 0));
}

static int	parse_line(t_data *d, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_or_comment(line))
		{
			if (!parse_line(line, d))
			{
				// free_next_line(line, fd); will remove the rest of the lines
				return (error_msg("wrong parser ig", 0));
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

// checks if the file is legit and runs parsing operation code 67
int	parse_file(t_data *data, char *file)
{
	int	fd;

	(void)data;
	fd = open(file, O_RDONLY);
	if (fd < 0 || !check_ext(file))
	{
		if (fd >= 0)
			(close(fd));
		return (error_msg(INVALID_FILE, 0));
	}
	if (parse_line(data, fd))
		return (error_msg("parsing FAILED!", 0));
	return (1);
}
