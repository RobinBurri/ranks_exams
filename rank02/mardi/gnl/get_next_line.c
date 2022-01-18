#include "get_next_line.h"

int ft_strlen(char *s)
{
	int i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char *join(char *s, char c)
{
	char *ns;
	int i = 0;
	int len = ft_strlen(s);
	ns = (char *)malloc(len + 2);
	if (!ns)
		return (0);
	while (i < len)
	{
		ns[i] = s[i];
		i++;
	}
	ns[i] = c;
	ns[i + 1] = 0;
	if (s)
		free(s);
	return (ns);
}

char *get_next_line(int fd)
{
	char c;
	char *s;
	static t_info info = {.fd = -1};

	s = 0;
	if (fd != info.fd)
		if (!check_init(fd, &info))
			return 0;
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

#include <fcntl.h>
#include <stdio.h>
int main()
{
	char *l;
	int fd;

	fd = open("t.txt", 0);
	while ((l = get_next_line(fd)) != NULL)
	{
		printf("%s", l);
	}
	return (0);
}
