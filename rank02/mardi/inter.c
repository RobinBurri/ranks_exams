#include <unistd.h>

int isdl(char *s, char c)
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

void	sol(char *s1, char *s2)
{
	int i = 0;
	int f[255];
	while (i < 255)
		f[i++] = 0;
	i = 0;
	while (s1[i])
	{
		if (f[(int)s1[i]] == 0 && isdl(s2, s1[i]))
		{
			f[(int)s1[i]] = 1;
			write(1, &s1[i], 1);
		}
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (f[(int)s2[i]] == 0 && isdl(s1, s2[i]))
		{
			f[(int)s2[i]] = 1;
			write(1, &s2[i], 1);
		}
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac != 3)
	{
		write(1, "\n", 1);
		return (1);
	}
	sol(av[1], av[2]);
	return (0);
}
