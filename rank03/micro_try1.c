#include "micro_try1.h"

int W;
int H;
char BG;
char **TAB;

int msg_err(FILE *fd, int err)
{
	if (err == 2)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		if (fd)
			fclose(fd);
		return (err);
	}
	else if (err == 1)
		write(1, "Error: argument\n", 16);
	else
	{
		for (int i = 0; i < H; i++)
		{
			write(1, TAB[i], W);
			write(1, "\n", 1);
			free(TAB[i]);
		}
		free(TAB);
	}
	if (fd)
		fclose(fd);
	return (err);
}

float in_rect(int col, int line, shape *rct)
{
	if (col < rct->x || (rct->x + rct->w) < col || line < rct->y || (rct->y + rct->h) < line)
		return (0);
	else if (col - rct->x < 1.000 || (rct->x + rct->w) - col < 1.000 || line - rct->y < 1.000 || (rct->y + rct->h) - line < 1.000)
		return (2);
	return (1);
}

int main(int argc, char **argv)
{
	FILE *fd;
	float sqr;
	int res;
	shape rct;
	fd = NULL;

	if (argc != 2)
		return (msg_err(fd, 1));
	if ((fd = fopen(argv[1], "r")))
	{
		if ((res = fscanf(fd, "%d %d %c", &W, &H, &BG)) == 3)
		{
			if (W <= 300 && W > 0 && H <= 300 && H > 0)
			{
				TAB = malloc(H * sizeof(char *));
				for (int i = 0; i < H; i++)
				{
					TAB[i] = malloc(W);
					memset(TAB[i], BG, W);
				}
				while (1)
				{
					res = fscanf(fd, "\n%c %f %f %f %f %c", &rct.t, &rct.x, &rct.y, &rct.w, &rct.h, &rct.c);
					if (res == -1)
						return (msg_err(fd, 0));
					else if (res != 6 || rct.w <= 0 || rct.h <= 0 || (rct.t != 'r' && rct.t != 'R'))
						break;
					for (int line = 0; line < H; line++)
					{
						for (int col = 0; col < W; col++)
						{
							sqr = in_rect(col, line, &rct);
							if (rct.t == 'r' && sqr == 2)
								TAB[line][col] = rct.c;
							else if (sqr && rct.t == 'R')
								TAB[line][col] = rct.c;
						}
					}
				}
			}
		}
	}
	return (msg_err(fd, 2));
}
