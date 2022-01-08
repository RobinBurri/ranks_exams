#include <unistd.h>
#include "get_next_line.h"

#include <stdio.h>

int	init_check(int fd, t_read *info)
{
	info->pos = 0;
	info->fd = fd;
	info->max = read(info->fd, info->data, BUFFER_SIZE);
	if (info->max < 0)
		return (0);
	else
		return (1);
}

char	read_check(t_read *info)
{
	char	result;

	if (info->pos >= info->max)
	{
		info->max = read(info->fd, info->data, BUFFER_SIZE);
		info->pos = 0;
		if (info->max <= 0)
			return (0);
	}
	result = info->data[info->pos];
	info->pos++;
	return (result);
}
/*
#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd = open("hello.c", 0);
	char *line = get_next_line(fd);
	while(line)
	{
		printf("line: '%s'\n\n", line);
		line = get_next_line(fd);
	}
}*/
