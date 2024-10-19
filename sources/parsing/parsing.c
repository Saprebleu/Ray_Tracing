/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:28:00 by tjarross          #+#    #+#             */
/*   Updated: 2024/10/19 14:28:03 by tjarross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"
#include "world.h"
#include "parsing.h"

int	parse_line(const char *line, t_world *world)
{
	char	**line_split;
	int		i;

	line_split = ft_split(line, ' ');
	if (line_split == NULL)
		return (printf("Error\nSplitting line failed\n"), -1);
	i = 0;
	while (line_split[i] && line_split[i][0] == '\0')
		i++;
	if (line_split[i] == NULL)
		return (0);
	if (0 == ft_strncmp(line_split[i], "A", 2))
		return (parse_ambient(line_split + i + 1, world));
	if (0 == ft_strncmp(line_split[i], "C", 2))
		return (parse_camera(line_split + i + 1, world));
	if (0 == ft_strncmp(line_split[i], "L", 2))
		return (parse_light(line_split + i + 1, world));
	if (0 == ft_strncmp(line_split[i], "sp", 3))
		return (parse_sphere(line_split + i + 1, world));
	if (0 == ft_strncmp(line_split[i], "pl", 3))
		return (parse_plane(line_split + i + 1, world));
	if (0 == ft_strncmp(line_split[i], "cy", 3))
		return (parse_cylinder(line_split + i + 1, world));
	return (printf("Error\nInvalid element type '%s'\n", line_split[i]), -2);
}

bool	file_has_extension(const char *pathname, const char *extension)
{
	const char	*tmp_filename;
	char		*tmp_extension;

	tmp_filename = ft_strrchr(pathname, '/');
	if (tmp_filename != NULL)
		tmp_filename += 1;
	else
		tmp_filename = pathname;
	tmp_extension = ft_strrchr(tmp_filename, '.');
	if (tmp_extension == NULL || tmp_extension == tmp_filename)
		return (false);
	return (0 == ft_strncmp(tmp_extension + 1, extension,
			ft_strlen(extension) + 1));
}

int	parse_rt(const char *pathname, t_world *world)
{
	int		fd;
	char	*line;

	ft_memset(world, 0, sizeof(t_world));
	if (false == file_has_extension(pathname, "rt"))
		return (printf("Error\nBad filename extension\n"), -1);
	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCannot open file '%s': %s\n",
				pathname, strerror(errno)), -2);
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (0 != parse_line(line, world))
			return (free(world->objects), free(line), -3);
		free(line);
	}
	close(fd);
	if (world->has_camera == false)
		return (free(world->objects), printf("Error\nNo camera found\n"), -4);
	return (0);
}
