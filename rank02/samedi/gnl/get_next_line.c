#include "get_next_line.h"

static int ft_strlen(char *s)
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
	char *ns;
	int len;
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
	ns[i + 1] = 0;
	if (s)
		free(s);
	return (ns);
}

char	*get_next_line(int fd)
{
	static t_info info = {.fd = -1};
	char *s;
	char c;

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
// #include <stdio.h>
// #include <fcntl.h>
// int main()
// {
// 	int fd = open("hello.txt", 0);
// 	char *line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s",line);
// 		line = get_next_line(fd);
// 	}
// 	return (0);
// }
