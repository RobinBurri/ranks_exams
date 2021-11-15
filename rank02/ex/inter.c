/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 07:00:47 by rburri            #+#    #+#             */
/*   Updated: 2021/11/15 07:36:15 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

int ft_is_double(char *str, char c)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
int ft_solve(char *s1, char *s2)
{
	int i = 0;
	int array[255];
	while (i < 255)
		array[i++] = 0;
	i = 0;
	while (s1[i])
	{
		if (ft_is_double(s2, s1[i]) == 1 
				&& array[(unsigned char)s1[i]] == 0)
		{
			array[(unsigned char)s1[i]] = 1;
			ft_putchar(s1[i]);
		}
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (ft_is_double(s1, s2[i]) == 1 
				&& array[(unsigned char)s2[i]] == 0)
		{
			array[(unsigned char)s2[i]] = 1;
			ft_putchar(s2[i]);
		}
		i++;
	}
	ft_putchar('\n');
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	ft_solve(argv[1], argv[2]);	
	return (0);
}
