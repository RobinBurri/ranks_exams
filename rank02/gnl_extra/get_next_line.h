#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct s_read
{
	int		fd;
	int		pos;
	int		hasread;
	char	data[BUFFER_SIZE];
}	t_read;

int		init_check(int fd, t_read *info);
char	read_check(t_read *info);
char	*get_next_line(int fd);

#endif
