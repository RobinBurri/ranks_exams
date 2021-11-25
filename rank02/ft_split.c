/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:49:01 by rburri            #+#    #+#             */
/*   Updated: 2021/11/25 14:58:30 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	ft_cnt_words(const char *str, char c)
{
	int	trigger;
	int	words;

	words = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			words++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (words);
}

void	ft_write_str(char *dest, char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_make_str(char **split, char *str, char c)
{
	int	i;
	int	j;
	int	strnum;

	strnum = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{	
			j = 0;
			while (str[i + j] != c && str[i + j] != '\0')
				j++;
			split[strnum] = (char *)malloc(sizeof(char) * (j + 1));
			if (split[strnum] == NULL)
				return ;
			ft_write_str(split[strnum], str + i, c);
			i += j;
			strnum++;
		}
	}
}

char	**ft_split(char *str, char c)
{
	int		words;
	char	**split;

	words = ft_cnt_words(str, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (split == NULL)
		return (NULL);
	split[words] = NULL;
	ft_make_str(split, str, c);
	return (split);
}

int	main(void)
{
	int		i;
	char	**array_of_str;
	char	*str;

	str = "Hello there, how are you, today?";
	i = 0;
	array_of_str = ft_split(str, ',');
	while (array_of_str[i] != NULL)
		printf("%s\n", array_of_str[i++]);
}
