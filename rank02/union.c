/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 07:36:46 by rburri            #+#    #+#             */
/*   Updated: 2021/11/15 08:25:50 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_is_double(char *s, char c)
{
	int i = 0;
	while (s[i++])
	{
		if (c == s[i])
			return (1);
	}
	return (0);
}
int ft_solve(char *s1, char *s2)
{
	int i = 0;
	int flags[255];
	while (i < 255)
		flags[i++] = 0;
	i = 0;
	while (s1[i])
	{
		if ((ft_is_double(s2, s1[i]) == 1 || ft_is_double(s1, s1[i]) == 1) && flags[(unsigned char)s1[i]] == 0)
		{
			flags[(unsigned char)s1[i]] = 1;
			ft_putchar(s1[i]);
		}
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if ((ft_is_double(s1, s2[i]) == 1 || ft_is_double(s2, s2[i]) == 1) && flags[(unsigned char)s2[i]] == 0)
		{
			flags[(unsigned char)s2[i]] = 1;
			ft_putchar(s2[i]);
		}
		i++;
	}
	ft_putchar('\n');
	return (0);
}
int main(int ac, char **av)
{
	if (ac != 3)
		return (1);
	ft_solve(av[1], av[2]);
	return (0);
}
