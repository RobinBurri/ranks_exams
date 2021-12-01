#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUFFER_SIZE 1

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

char *ft_strdup(char *s, int f)
{
	int i = 0;
	int len;
	char *ns;

	len = ft_strlen(s);
	ns = (char *)malloc(1 * len + 1);
	if (ns == NULL)
		return (NULL);
	while (s[i])
	{
		ns[i] = s[i];
		i++;
	}
	ns[i] = '\0';
	if (f == 1)
		free(s);
	return (ns);
}

char *ft_substr(char *s, int start, int len, int f)
{
	char *ns;
	int max_len;
	int i = 0;
	int s_len;

	s_len = ft_strlen(s);
	if (len > s_len + 1)
		len = s_len + 1;
	ns = (char *)malloc(1 * len + 1);
	if (ns == NULL)
		return (NULL);
	while (start < s_len &&  i < len)
		ns[i++] = s[start++];
	ns[i] = '\0';
	if (f == 1)
		free(s);
	return (ns);
}

// char *ft_substr(char *s, int start, int len, int f)
// {
// 	char *ns;
// 	int s_len;
// 	int i = 0;
	
// 	if (!*s)
// 		return (NULL);
// 	s_len = ft_strlen(s);
// 	if (len > s_len + 1)
// 		len = s_len + 1;
// 	ns = (char *)malloc(1 * len + 1);
// 	if (ns == NULL)	
// 		return (NULL);
// 	while (start < s_len && i < len)
// 		ns[i++] = s[start++];
// 	ns[i] = '\0';
// 	if (f == 1)
// 		free(s);
// 	return (ns);
// }

char *ft_strjoin(char *s1, char *s2)
{
	char *ns;
	int i = 0;
	int s_len;
	int j = 0;

	s_len = ft_strlen(s1) + ft_strlen(s2);;
	ns = (char *)malloc(1 * s_len +1);
	if (ns == NULL)
		return (NULL);
	while (s1[i])
		ns[j++] = s1[i++];
	i = 0;
	while (s2[i])
		ns[j++] = s2[i++];
	ns[j] = '\0';
	free(s1);
	return  (ns);
}

int ft_checknl(char *s)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
static char	*ft_send_line(char **str)
{
	char		*line;
	int			len;
	int check;

	check = ft_checknl(*str);
	line = ft_substr(*str, 0, check + 1, 0);
	len = (ft_strlen(*str) - ft_strlen(line));
	*str = ft_substr(*str, check + 1, len, 1);
	return (line);
}

static char	*ft_send_last_line(char *str, int ints[])
{
	static int	i = 0;

	if ((ints[1] == 0 && (ft_strcmp(str, "") == 0)) || ints[1] == -1
		|| (ints[2]++ == 1 && ints[1] == 0))
	{
		i = 1;
		free(str);
	}
	if (i == 1)
	{
		ints[0] = 1;
		ints[1] = 1;
		ints[2] = 1;
		i = 0;
		return (NULL);
	}
	i = 1;
	ints[0] = 1;
	ints[1] = 1;
	ints[2] = 1;
	return (str);
}

static char	*ft_str_loader(char **str, int ints[])
{
	if (ints[0] == 1)
	{
		*str = ft_strdup("", 0);
		ints[0] = 0;
	}
	else
	{
		*str = ft_strdup(*str, 1);
	}
	return (*str);
}

char *get_next_line(int fd)
{
	static char *str;
	char buff[BUFFER_SIZE + 1];
	static int ints[3] = {1, 1, 1};
	int check;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_str_loader(&str, ints);
	while (ints[1] > 0)
	{
		ints[1] = read(fd, buff, BUFFER_SIZE);
		if (ints[1] == -1)
			return (ft_send_last_line(str, ints));
		buff[ints[1]] = '\0';
		str = ft_strjoin(str, buff);
		if ((check = ft_checknl(buff)) != -1)
			return (ft_send_line(&str));
	}
	if ((check = ft_checknl(str)) != -1)
		return (ft_send_line(&str));
	return (ft_send_last_line(str, ints));
}



int main(void)
{
	int fd;
	int start = 1;
	char *s = NULL;

	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
		return (-1);
	while (start != 0)
	{
		s = get_next_line(fd);
		if (s != NULL)
		{
			printf("%s", s);
			free(s);
		}
		else
			start = 0;
	}
	close(fd);
	return (1);
}

