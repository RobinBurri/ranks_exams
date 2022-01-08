#include "get_next_line.h"

int	strlen2(char *s)
{
	int	i;

	i = 0;
	if (s == 0)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*join(char *str, char c)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = strlen2(str);
	tmp = malloc(len + 2);
	if (tmp == 0)
		return (0);
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = 0;
	if (str)
		free(str);
	return (tmp);
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