#ifndef MI_H
# define MI_H

# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <stdlib.h>

typedef struct s_data
{
	int pipe;
	int status;
	int old_stdin;
} 			t_data;

#endif