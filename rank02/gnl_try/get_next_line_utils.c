 #include "get_next_line.h"

int	init_check(int fd, t_info *info)
{
	info->fd = fd;
	info->pos = 0;
	info->hasread = read(info->fd, info->buf, BUFFER_SIZE);
	if (info->hasread < 0)
		return (0);
	else
		return (1);
}

char read_check(t_info *info)
{
	char res;

	if (info->pos >= info->hasread)
	{
		info->hasread = read(info->fd, info->buf, BUFFER_SIZE);
		info->pos = 0;
		if (info->hasread <= 0)
			return (0);
	}
	res =info->buf[info->pos];
	info->pos++;
	return (res);
}