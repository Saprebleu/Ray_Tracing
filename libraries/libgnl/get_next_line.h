#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

char	*begins_after_n(char *s);
int		n_is_nth_char_of(char *str);
char	*get_next_line(int fd);

#endif
