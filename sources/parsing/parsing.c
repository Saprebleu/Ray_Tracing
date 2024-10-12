#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"
#include "parsing.h"

bool	file_has_extension(const char *pathname, const char *extension)
{
	char	*tmp;

	tmp = ft_strrchr(pathname, '.');
	if (tmp == NULL)
		return (false);
	return (0 == ft_strncmp(tmp + 1, extension, ft_strlen(extension)));
}

int	parse_rt(const char *pathname/*, t_world *world*/)
{
	int		fd;
	char	*line;

	if (false == file_has_extension(pathname, "rt"))
		return (-1);
	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n%s\n", strerror(errno));
		return (-2);
	}
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		// if (0 != parse_line(line, world))
		// 	return (free(world->objects), free(line), -3);
		free(line);
	}
	close(fd);
	return (0);
}
