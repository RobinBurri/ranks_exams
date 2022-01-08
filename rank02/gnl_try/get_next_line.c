 #include "get_next_line.h"

 int mystrlen(char *s)
 {
	 int i;
	 
	 i = 0;
	 if (s == 0)
	 	return (0);
	while (s[i])
		i++;
	return (i);
 }

 char	*join(char *s, char c)
 {
	 char	*tmp;
	 int	len;
	 int 	i;

	i = 0;
	len = mystrlen(s);
	tmp = malloc(len + 2);
	if (tmp == 0)
		return (0);
	while (i < len)
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = 0;
	if (s)
		free(s);
	return (tmp);
 }
 
 char	*get_next_line(int fd)
 {
	static t_info	info = {.fd = -1};
	char 			c;
	char 			*s;

	s = 0;
	if (info.fd != fd)
		if (!init_check(fd, &info))
			return (0);
	c = read_check(&info);
	while (c)
	{
		s = join(s, c);
		if (c == '\n')
			return (s);
		c = read_check(&info);
	}
	return (s);
 }