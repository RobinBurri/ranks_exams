#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BS 1

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s1)[i]);
}

int ft_strlen(char *s)
{
	int i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}


char *ft_strdup(char *s, int f)
{
	int i = 0;
	int len;
	char *ns;

	len = ft_strlen(s);
	ns = (char *)malloc(len + 1);
	if (ns == NULL)
		return (NULL);
	while (s[i])
	{
		ns[i] = s[i];
		i++;
	}
	ns = '\0';
	if (f == 1)
		free(s);
	return (ns);
}

char *ft_strjoin(char *s, char *buf)
{
	int i = 0;
	int j = 0;
	int len;
	char *ns;

	len = ft_strlen(s) + ft_strlen(buf);
	ns = (char *)malloc(len + 1);
	if (ns == NULL)
		return (NULL);
	while (s[i] && (!(!s)))
	{
		ns[j] = s[i];
		i++;
		j++;
	}
	i = 0;
	while (buf[i])
		ns[j++] = buf[i++];
	ns = '\0';
	return (ns);
}

int ft_hasnl(char *s)
{
	int i =0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
char *ft_substr(char *s, int start, int len, int f)
{
	char *ns;
	int s_len;
	int i = 0;
	
	if (!*s)
		return (NULL);
	s_len = ft_strlen(s);
	if (len > s_len + 1)
		len = s_len + 1;
	ns = (char *)malloc(1 * len + 1);
	if (ns == NULL)	
		return (NULL);
	while (start < s_len && i < len)
		ns[i++] = s[start++];
	ns[i] = '\0';
	if (f == 1)
		free(s);
	return (ns);
}

char *ft_send_line(char **s, int ck)
{
	char *line;
	int len;

	line = ft_substr(*s, 0, ck + 1, 0);
	len = ft_strlen(*s) - ft_strlen(line);
	*s = ft_substr(*s, ck + 1, len, 1);
	return (line);
}

char *ft_send_last(char *s, int ints[])
{
	static int i = 0;

	if ((ints[1] == 0 && (ft_strcmp(s, "") == 0)) || ints[1] == -1 || (ints[2]++ == 1 && ints[1] == 0))
	{
		i = 1;
		free(s);
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
	return (s);
}

char *get_next_line(int fd)
{
	static char *s;
	static int ints[3] = {1, 1, 1};
	int ck;
	char buf[BS + 1];

	if (fd < 0)
		return (NULL);
	if (ints[0] == 1)
	{
		s = ft_strdup("", 0);
		ints[0] = 0;
	} else {
		s = ft_strdup(s, 1);
	}
	while (ints[1] > 0)
	{
		ints[1] = read(fd, buf, BS);
		if (ints[1] == -1 || (ints[2]++ == 1 && ints[1] == 0))
			return (ft_send_last(s, ints));
		buf[ints[1]] = '\0';
		s = ft_strjoin(s, buf);
		ck = ft_hasnl(buf);
		if (ck != -1)
			ft_send_line(&s, ck);
	}
	ck = ft_hasnl(buf);
	if (ck != -1)
			ft_send_line(&s, ck);
	return (ft_send_last(s, ints));
}

int main()
{
	int fd;
	int f;
	char *s = "";
	int start = 1;

	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("OPEN");
		return (1);
	}
	while (start)
	{
		s = get_next_line(fd);
		if (s != NULL)
		{
			printf("%s", s);
			free(s);
		}
		else {
			start = 0;
		}
	}
	f = close(fd);
	{
		printf("close");
		return (1);
	}
	return (0);
}
