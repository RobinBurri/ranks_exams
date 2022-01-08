#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_info
{
	int fd;
	int pos;
	int hasread;
	char buf[BUFFER_SIZE];
} 			t_info;

int	init_check(int fd, t_info *info);
char	*get_next_line(int fd);
char 	read_check(t_info *info);

#endif