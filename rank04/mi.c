#include "mi.h"

int ft_sl(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

void ft_cd(char **av)
{
	int i = 0;
	char *arg_er = "error: cd: bad arguments\n";
	char *cd_err = "error: cd: cannot change directory to ";

	while (av[i])
		i++;
	if (i != 2)
		write(2, arg_er, ft_sl(arg_er));
	if (chdir(av[i]) == -1)
	{
		write(2, cd_err, ft_sl(cd_err));
		write(2, av[i], ft_sl(av[i]));
		write(2, "\n", 1);
	}
}

void	ft_exec(t_data *data, char **av, char **envp)
{
	int pid;
	int pipe_fd[2];
	char *fatal_er = "error: fatal";
	char *exec_er = "error: cannot execute ";

	if (av[0] == NULL)
		return ;
	if (strcmp(av[0], "cd") == 0)
	{
		ft_cd(av);
		return ;
	}
	if (data->pipe == 1 && pipe(pipe_fd) == -1)
	{
		write(2, fatal_er, ft_sl(fatal_er));
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		write(2, fatal_er, ft_sl(fatal_er));
		exit(1);
	}
	if (pid == 0)
	{
		if (data->pipe == 1)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
		execve(av[0], av, envp);
		write(2, exec_er, ft_sl(av[0]));
		write(2, av[0], ft_sl(av[0]));
		write(2, "\n", 1);
		close(data->old_stdin);
		exit(1);
	}
	else
	{
		if (data->pipe == 1)
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
		}
		else
			dup2(data->old_stdin, STDIN_FILENO);
		waitpid(pid, &data->status, 0);
	}
}

int main(int ac, char **av, char **envp)
{
	int i = 1;
	int j = 1;
	t_data data;
	data.old_stdin = dup(STDIN_FILENO);
	data.pipe = 0;
	data.status = 0;

	while (av[i])
	{
		if (strcmp(av[i], "|") == 0 || strcmp(av[i], ";") == 0)
		{
			if (strcmp(av[i], "|") == 0)
				data.pipe = 1;
			av[i] = NULL;
			ft_exec(&data, &av[j], envp);
			data.pipe = 0;
			j = i + 1;
		}
		else if (av[i + 1] == NULL)
			ft_exec(&data, &av[j], envp);
		i++;
	}
	close(data.old_stdin);
	return (0);
}