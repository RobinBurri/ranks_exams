#include <unistd.h>

void ft_putchar(char s)
{
	write(1, &s, 1);
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

int ft_solve(char *s1, char *s2)
{
	int flags[257];
	int i = 0;
	while (i < 257)
		flags[i++] = 0;
	i = 0;
	while (s1[i])
	{
		if ((ft_isdle(s2, s1[i]) == 1) && flags[s1[i]] == 0)
		{
			flags[s1[i]] = 1;
			ft_putchar(s1[i]);
		}
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if ((ft_isdle(s1, s2[i]) == 1) && flags[s2[i]] == 0)
		{
			flags[s2[i]] = 1;
			ft_putchar(s2[i]);
		}
		i++;
	}
	ft_putchar('\n');
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 3)
		ft_putchar('\n');
	ft_solve(argv[1], argv[2]);
	return (0);
}