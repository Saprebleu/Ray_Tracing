/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:28:00 by tjarross          #+#    #+#             */
/*   Updated: 2025/01/13 18:30:48 by tjarross         ###   ########.fr       */
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

int	parse_elements(char **line_split, int i, t_world *world)
{
	int	ret;

	if (0 == ft_strncmp(line_split[i], "A", 2))
		ret = parse_ambient(line_split + i + 1, world);
	else if (0 == ft_strncmp(line_split[i], "C", 2))
		ret = parse_camera(line_split + i + 1, world);
	else if (0 == ft_strncmp(line_split[i], "L", 2))
		ret = parse_light(line_split + i + 1, world);
	else if (0 == ft_strncmp(line_split[i], "sp", 3))
		ret = parse_sphere(line_split + i + 1, world);
	else if (0 == ft_strncmp(line_split[i], "pl", 3))
		ret = parse_plane(line_split + i + 1, world);
	else if (0 == ft_strncmp(line_split[i], "cy", 3))
		ret = parse_cylinder(line_split + i + 1, world);
	else
	{
		printf("Error\nInvalid element type '%s'\n", line_split[i]);
		ret = -100;
	}
	return (ft_free_split(line_split), ret);
}

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
		return (ft_free_split(line_split), 0);
	return (parse_elements(line_split, i, world));
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

void	put_indexes(t_world *world)
{
	int	i;

	i = -1;
	while (++i < world->nb_objects)
		world->objects[i].index = i;
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
	if (world->nb_camera != 1 || world->nb_ambient != 1 || world->nb_light != 1)
		return (free(world->objects),
			printf("Error\nMissing or multiple objects\n"), -4);
	return (put_indexes(world), close(fd), 0);
}
