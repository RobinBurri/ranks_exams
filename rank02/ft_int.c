#include <unistd.h>

int ft_isd(char *s, char c)
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

void ft_soluc(char *s1, char *s2)
{
	int flags[255];
	int i = 0;
	while (i < 255)
		flags[i++] = 0;
	i = 0;
	while (s1[i])
	{
		if (flags[s1[i]] == 0 && ft_isd(s2, s1[i]) == 1)
		{
			write(1, &s1[i], 1);
			flags[s1[i]] = 1;
		}
		i++;
	}
	i = 1;
	while (s2[i])
	{
		if (flags[s2[i]] == 0 && ft_isd(s1, s2[i]) == 1)
		{
			write(1, &s2[i], 1);
			flags[s2[i]] = 1;
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
	ft_soluc(av[1], av[2]);
	return (0);
}