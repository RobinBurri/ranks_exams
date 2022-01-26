#include <unistd.h>



void soluction(char *s1, char *s2)
{
	int f[255];
	int i = 0;
	while (i < 255)
		f[i++] = 0;
	i = 0;
	while (s1[i])
	{
		if (f[(int)s1[i]] == 0) 
		{
			f[(int)s1[i]] = 1;
			write(1, &s1[i], 1);
		}
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (f[(int)s2[i]] == 0 )
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
	soluction(av[1], av[2]);
	return (0);
}
