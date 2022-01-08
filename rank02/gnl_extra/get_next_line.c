#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

int	strlen2(char *str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*join(char *str, char c)
{
	char	*mem;
	int		i;
	int		len;

	i = 0;
	len = strlen2(str);
	mem = malloc(len + 2);
	if (mem == 0)
		return (0);
	while (i < len)
	{
		mem[i] = str[i];
		i++;
	}
	mem[i] = c;
	mem[i + 1] = 0;
	if (str)
		free(str);
	return (mem);
}

char	*get_next_line(int fd)
{
	static t_read	info = {.fd = -1};
	char			c;
	char			*str;

	str = 0;
	if (info.fd != fd)
		if (!init_check(fd, &info))
			return (0);
	c = read_check(&info);
	while (c)
	{
		str = join(str, c);
		if (c == '\n')
			return (str);
		c = read_check(&info);
	}
	return (str);
}