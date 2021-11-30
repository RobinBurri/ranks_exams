/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 08:13:17 by rburri            #+#    #+#             */
/*   Updated: 2021/11/30 13:43:56 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_check_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*ft_send_line(char **str, int check)
{
	char		*line;
	int			len;

	line = ft_substr(*str, 0, check + 1, 0);
	len = (ft_strlen(*str) - ft_strlen(line));
	*str = ft_substr(*str, check + 1, len, 1);
	return (line);
}

static char	*ft_send_last_line(char *str, int ints[])
{
	
	if ((ints[1] == 0 && (ft_strcmp(str, "") == 0)) || ints[1] == -1
		|| (ints[2] == 1 && ints[1] == 0))
	{
		ints[0] = 1;
		ints[1] = 1;
		ints[2] = 1;
		free(str);
		return (NULL);
	}
	else
	{
		ints[0] = 1;
		ints[1] = 1;
		ints[2] = 1;
		return (str);
	}
}

static char	*ft_str_loader(char **str, int ints[])
{
	if (ints[0] == 1)
	{
		*str = ft_strdup("", 0);
		ints[0] = 0;
	}
	else
	{
		*str = ft_strdup(*str, 1);
	}
	return (*str);
}

char	*get_next_line(int fd)
{	
	static char	*str;
	char		buf[BUFFER_SIZE + 1];
	static int	ints[] = {1, 1, 1};
	int			check;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_str_loader(&str, ints);
	while (ints[1] > 0)
	{
		ints[1] = read(fd, buf, BUFFER_SIZE);
		if (ints[1] == -1 || (ints[2]++ == 1 && ints[1] == 0))
			return (ft_send_last_line(str, ints));
		buf[ints[1]] = '\0';
		str = ft_strjoin(str, buf);
		if (ft_check_newline(buf) != -1)
		{
			check = ft_check_newline(str);
			return (ft_send_line(&str, check));
		}
	}
	check = ft_check_newline(str);
	if (check != -1)
		return (ft_send_line(&str, check));
	return (ft_send_last_line(str, ints));
}
