#include <fcntl.h>
#include <stdio.h>

int	get_next_line(int fd)
{
	
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