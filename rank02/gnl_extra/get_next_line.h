#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_read
{
	int		fd;
	int		pos;
	int		max;
	char	data[BUFFER_SIZE];
}	t_read;

int		init_check(int fd, t_read *info);
char	read_check(t_read *info);
char	*get_next_line(int fd);

#endif
