#include "get_next_line.h"

int check_init(int fd, t_info *info)
{
	info->fd = fd;
	info->pos = 0;
	info->hasread = read(info->fd, info->buf, BUFFER_SIZE);
	if (info->hasread < 0)
		return (0);
	else 
		return (1);
}

char check_read(t_info *info)
{
	char c;
	if (info->pos >= info->hasread)
	{
		info->pos = 0;
		info->hasread = read(info->fd, info->buf, BUFFER_SIZE);
		if (info->hasread <= 0)
			return (0);
	}
	c = info->buf[info->pos];
	info->pos++;
	return (c);
}
