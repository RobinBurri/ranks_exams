/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuchill <apuchill@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 17:31:30 by apuchill          #+#    #+#             */
/*   Updated: 2020/05/02 13:44:16 by apuchill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

#define MAIN(string)		"\033[1m\033[38;5;199m" string "\033[0m"
#define MAIN_1(string)		"\033[35m" string "\033[0m"
#define HEADER_1(string)	"\033[38;5;43m" string "\033[0m"
#define HEADER_2(string)	"\033[38;5;75m" string "\033[0m"
#define HIGHLIGHT(string)	"\033[38;5;191m" string "\033[0m"

void	test(int fd)
{
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
		{
			printf("%s", line);
			free(line);
		}
	close(fd);

}

int		main(void)
{
	printf(MAIN("=== • Program started • ===\n"));

	printf(MAIN_1("=== empty file ===\n"));
	int	fda;
	fda = open("txt_files/t_empty.txt", O_RDONLY);
	test(fda);

	printf(MAIN_1("=== 5 nl ===\n"));
	int	fdf;
	fdf = open("txt_files/5nl.txt", O_RDONLY);
	test(fdf);

	printf(MAIN_1("=== \\n file ===\n"));
	int	fdb;
	fdb = open("txt_files/t_n.txt", O_RDONLY);
	test(fdb);

	printf(MAIN_1("=== 43 NL ===\n"));
	int	fdi;
	fdi = open("txt_files/43_nl.txt", O_RDONLY);
	test(fdi);

	printf(MAIN_1("=== 43 WITH \n ===\n"));
	int	fdj;
	fdj = open("txt_files/43_wl.txt", O_RDONLY);
	test(fdj);

	printf(MAIN_1("=== Alternate line and nl ===\n"));
	int	fde;
	fde = open("txt_files/alt_ln.txt", O_RDONLY);
	test(fde);


	printf(MAIN_1("=== BIG LINE NO NL ===\n"));
	int	fdg;
	fdg = open("txt_files/bl_no.txt", O_RDONLY);
	test(fdg);

	printf(MAIN_1("=== BIG LINE WITH NL ===\n"));
	int	fdh;
	fdh = open("txt_files/bl_wh.txt", O_RDONLY);
	test(fdh);

	printf(MAIN_1("=== Le Petit Prince ===\n"));
	int	fdc;
	fdc = open("txt_files/t_ptiprinc.txt", O_RDONLY);
	test(fdc);
	
	printf(MAIN("=== • Program ended • ===\n\n"));
}
