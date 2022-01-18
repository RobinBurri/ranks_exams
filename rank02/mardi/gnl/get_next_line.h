#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

#include <stdlib.h>
#include <unistd.h>

typedef struct s_info
{
	int fd;
	int pos;
	int hasread;
	char buf[BUFFER_SIZE];
}				t_info;

int check_init(int fd, t_info *info);
char check_read(t_info *info);
char *get_next_line(int fd);
#endif
