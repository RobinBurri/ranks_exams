#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int ft_hasnl(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char *ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	int len;
	char *ns;

	len = ft_strlen(s1) + ft_strlen(s2);
	ns = (char *)malloc(1 * (len + 1));
	while(s1[i])
	{
		ns[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		ns[j] = s2[i];
		i++;
		j++;
	}
	ns[j] = '\0';
	free(s1);
	return (ns);
}

char *ft_strdup(char *s)
{
	int i = 0;
	int len;
	char *ns;

	len = ft_strlen(s);
	ns = (char *)malloc( 1 * (len + 1));
	if (ns == NULL)
		return (NULL);
	while (s[i])
	{
		ns[i] = s[i];
		i++;
	}
	ns[i] = '\0';
	return (ns);
}
char *ft_strdupf(char *s)
{
	int i = 0;
	int len;
	char *ns;

	len = ft_strlen(s);
	ns = (char *)malloc( 1 * (len + 1));
	if (ns == NULL)
		return (NULL);
	while (s[i])
	{
		ns[i] = s[i];
		i++;
	}
	ns[i] = '\0';
	free(s);
	return (ns);
}

char *ft_strncpy(char *str, int max)
{
	int i = 0;
	char *ns;

	ns = (char *)malloc(sizeof(char) * max + 2);
	if (ns == NULL)
		return (NULL);
	while (str[i] && max >= i)
	{
		ns[i] = str[i];
		i++;
	}
	ns[i] = '\0';
	return (ns);
}

int ft_send_line(char *str)
{
	int check;
	char *ns;

	check = ft_hasnl(str);
	ns = ft_strncpy(str, check);
	str = ft_strdupf(str + check);
	return (check);
}

int	get_next_line(int fd)
{
	static char *str;
	int i = 0;
	int ret = 1;
	char *buff[BUFFER_SIZE + 1];
	int check;
	int cnt;

	cnt = 0;
	check = 0;
	if (!str)
		str = ft_strdup("");
	while (ret != 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
			return (ret);
		str = ft_strjoin(str, buff[]);
		check = ft_hasnl(str);
		if (check != -1)
			cnt += ft_send_line(str);
	}
	cnt += ft_send_line(str);
	return (cnt);
}

int main()
{
	int fd;
	int ret;
	

	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		return (1);
	}

	printf("%s\n", get_next_line(fd));

	ret = close(fd);
	if (ret == -1)
	{
		printf("Error\n");
		return (1);
	}
}