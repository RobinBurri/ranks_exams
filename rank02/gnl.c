#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 1

int ft_strlen(char *s)
{
	if (!s)
		return (0);
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int ft_strcmp(char *s1, char *s2){

	int i = 0;
	while (s1 && s1[i] == s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

char *ft_strdup(char *s, int f)
{
	int i = 0;
	char *ns;
	int len;

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

char *ft_substr(char *s, int start, int len, int f)
{
	int i = 0;
	int j = 0;
	char *ns;
	int s_len;
	int max_len;

	s_len = ft_strlen(s);
	if (len > s_len)
		max_len = s_len;
	else
		max_len = len;
	ns = (char *)malloc(max_len + 1);
	if (ns == NULL)
		return (NULL);
	while (s[i] && i < len && i + start < max_len)
		ns[j++] = s[start + i++];
	ns[j] = '\0';
	if (f == 1)
		free(s);
	return (ns);
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

char	*ft_sendl(char **s)
{
	char *line;
	int ck;
	int len;
	ck = ft_hasnl(*s);
	line = ft_substr(*s, 0, ck, 0);
	len = (ft_strlen(*s) - ft_strlen(line));
	*s = ft_substr(*s, ck +1, len, 1);
	return (line);
}
char 	*ft_s_lastl(char *s, int ints[])
{
	int i = 0;
	if (ints[1] == -1 || ints[2] == 2 && ints[1] == 0)
	{
		i = 1;
		free(s);
	}
	
	if (i == 1)
	{
		ints[0] = 1;
		ints[1] = 1;
		ints[2] = 1;
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

char *ft_gnl(int fd)
{
	int ck;
	static char *s;
	static int ints[3] = {1, 1, 1};
	char buf[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (ints[0] == 1)
	{
		ints[0] = 0;
		s = ft_strdup("", 0);
	}
	else if (ints[0] == 0)
		s = ft_strdup(s, 1);
	while (ints[1] != 0)
	{
		ints[1] = read(fd, buf, BUFFER_SIZE);
		if (ints[1] == -1 || (ints[2]++ == 1 && ints[1] == 0))
			return (ft_s_lastl(s, ints));
		s = ft_strjoin(s, buf);
		ck = ft_hasnl(buf);
		if (ck != -1)
			return (ft_sendl(&s)); 
	}
	if ((ck = ft_hasnl(s) != -1))
			ft_sendl(&s);
	return (ft_s_lastl(s, ints));
}

int main()
{
	int fd;
	char *s;

	fd = open("t.txt", O_RDONLY);
	if (fd == -1)
		printf("error open");

	while (s != NULL)
	{
		s = ft_gnl(fd);
		if (s != NULL)
			printf("%s\n", s);
			free(s);
	}
	fd = close(fd);
	if (fd == -1)
		printf("error close");

	return (0);
}