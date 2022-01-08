#include "get_next_line.h"

int	init_check(int fd, t_read *info)
{
	info->fd = fd;
	info->pos = 0;
	info->hasread = read(info->fd, info->data, BUFFER_SIZE);
	if (info->hasread < 0)
		return (0);
	else
		return (1);
}

char	read_check(t_read *info)
{
	char	result;

	if (info->pos >= info->hasread)
	{
		info->hasread = read(info->fd, info->data, BUFFER_SIZE);
		info->pos = 0;
		if (info->hasread <= 0)
			return (0);
	}
	result = info->data[info->pos];
	info->pos++;
	return (result);
}

// int main()
// {
// 	int fd = open("hello.txt", 0);
// 	char *line = get_next_line(fd);
// 	while(line)
// 	{
// 		printf("line: '%s'\n\n", line);
// 		line = get_next_line(fd);
// 	}
// }
