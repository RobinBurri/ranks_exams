#include "get_next_line.h"

int ft_strlen(char *s)
{
	int i = 0;
	if (s == 0)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char *join(char *s, char c)
{
	int len;
	char *ns;
	int i = 0;
	len = ft_strlen(s);
	ns = (char *)malloc(len + 2);
	if (!ns)
		return (0);
	while (i < len)
	{
		ns[i] = s[i];
		i++;
	}
	ns[i] = c;
	ns [i + 1] = 0;
	if (s)
		free(s);
	return (ns);
}

char *get_next_line(int fd)
{
	static t_info info = {.fd = -1};
	char c;
	char *s;

	s = 0;
	if (fd != info.fd)
		if (!check_init(fd, &info))
				return (0);
	c = check_read(&info);
	while (c)
	{
		s = join(s, c);
		if (c == '\n')
			return (s);
		c = check_read(&info);
	}
	return (s);
}
