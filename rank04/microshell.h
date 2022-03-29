#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <stdlib.h>
//malloc, free
# include <unistd.h>
//write close fork execve dup2 pipe
# include <sys/wait.h>
//waitpid
# include <signal.h>
//signal
# include <string.h>
//strncmp  

typedef struct	s_data
{
	int status;
	int	stdout_pipe;
	int	old_stdin;
}				t_data;

#endif