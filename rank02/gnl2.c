#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
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
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]); 
}

int ft_hasnl(char *s)
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

char *ft_strdup(char *s, int f)
{
	int i = 0;
	char *ns;
	int len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	ns = (char *)malloc(len + 1);
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

char *ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	char *ns;
	int len;

	len = ft_strlen(s1) + ft_strlen(s2);
	ns = (char *)malloc(len + 1);
	if (ns == NULL)
		return (NULL);
	while (s1[i])
		ns[j++] = s1[i++];
	i = 0;
	while (s2[i])
		ns[j++] = s2[i++];
	ns[j] = '\0';
	return (ns);
}

char *ft_substr(char *s1, int start, int len, int f)
{
	int i = 0;
	char *ns;
	int max_len;

	if (!s1)
		return (NULL);
	if (len > ft_strlen(s1) + 1)
		max_len = ft_strlen(s1) + 1;
	else
		max_len = len;
	ns = (char *)malloc(max_len + 1);
	if (ns == NULL)
		return (NULL);
	while (s1[i] && i < max_len && start < ft_strlen(s1))
		ns[i++] = s1[start++];
	ns[i] = '\0';
	if (f == 1)
		free(s1);
	return (ns);
}

char *send_last_line(char *s, int ints[])
{
	if (ints[1] == -1 || (ints[2] == 2 && ints[1] == 0)
		|| (ints[1] == 0 && ft_strcmp(s, "") == 0))
	{
		ints[0] = 1;
		ints[1] = 1;
		ints[2] = 1;
		free(s);
		return (NULL);
	}
	else
	{
		ints[0] = 1;
		ints[1] = 1;
		ints[2] = 1;
		return (s);
	}

}

char *send_line(char **s)
{
	int check;
	char *line;
	int len;

	check = ft_hasnl(*s);
	line = ft_substr(*s, 0, check + 1, 0);
	len = ft_strlen(*s) - ft_strlen(line); 
	*s = ft_substr(*s, check + 1, len, 1);
	return (line);
}

char *get_next_line(int fd)
{
	static char *s;
	char buf[BUFFER_SIZE + 1];
	static int ints[3] = {1, 1, 1};
	int check;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (ints[0] == 1) 
	{
		s = ft_strdup("", 0);
		ints[0] = 0;
	}
	else
		s = ft_strdup(s, 1);
	while (ints[1] > 0)
	{
		ints[1] = read(fd, buf, BUFFER_SIZE);
		if (ints[1] == -1 || (ints[2]++ == 1 && ints[1] == 0))
			return (send_last_line(s, ints));
		buf[ints[1]] = '\0';
		s = ft_strjoin(s, buf);
		check = ft_hasnl(buf);
		if (check != -1)
			return (send_line(&s));
	}
	check = ft_hasnl(s);
	if (check != -1)
		return (send_line(&s));
	return (send_last_line(s, ints));
}

int main(void)
{
	int fd;
	char *s = "";

	fd = open("t.txt", O_RDONLY);
	while (s != NULL)
	{
		s = get_next_line(fd);
		if (s != NULL)
		{
			printf("%s", s);
			free(s);
		}
	}
	close(fd);
	return (0);
}