#include <unistd.h>

void	ft_solution(char *s1, char *s2)
{
	int flags[255];
	int i = 0;

	while (i < 255)
	{
		flags[i] = 0;
		i++;
	}
	i = 0;
	while (s1[i])
	{
		if (flags[s1[i]] == 0)
		{
			flags[s1[i]] = 1;
			write(1, &s1[i], 1);
		}
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (flags[s2[i]] == 0)
		{
			flags[s2[i]] = 1;
			write(1, &s2[i], 1);
		}
		i++;
	}
}

int main(int argc, char **av)
{
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (1);
	}
	ft_solution(av[1], av[2]);
	return (0);
}