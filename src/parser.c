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

// static int	read_lines(t_data *d, int fd)
// {
// 	char	*line;

// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (!ft_strncmp(line, "\n", 1) || ft_strncmp(line, "#", 1))
			
// 		line = get_next_line(fd);
// 	}
// 	return (1);
// }

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
	// if (read_lines(data, fd))
	return (1);
}
