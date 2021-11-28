#include <unistd.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

int ft_isdle(char *s, char c)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void ft_solve(char *s1, char *s2)
{
	int flags[255];
	int i = 0;
	while (i < 255)
		flags[i++] = 0;
	i = 0;
	while (s1[i])
	{
		if ((ft_isdle(s2, s1[i]) == 1 || ft_isdle(s1, s1[i]) == 1) && flags[s1[i]] == 0)
		{
			flags[s1[i]] = 1;
			ft_putchar(s1[i]);
		}
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if ((ft_isdle(s1, s2[i]) == 1 || ft_isdle(s2, s2[i]) == 1) && flags[s2[i]] == 0)
		{
			flags[s2[i]] = 1;
			ft_putchar(s2[i]);
		}
		i++;
	}
}


int main(int ac, char **av)
{
	if (ac != 3)
	{
		ft_putchar('\n');
		return (1);
	}
	ft_solve(av[1], av[2]);
	return (0);
}