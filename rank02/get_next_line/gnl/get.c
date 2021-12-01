#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s1)[i]);
}
int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}


char *ft_substr(char *s, int start, int len, int f)
{
	char *ns;
	int s_len;
	int i = 0;
	
	if (!*s)
		return (NULL);
	s_len = ft_strlen(s);
	if (len > s_len + 1)
		len = s_len + 1;
	ns = (char *)malloc(1 * len + 1);
	if (ns == NULL)	
		return (NULL);
	while (start < s_len && i < len)
		ns[i++] = s[start++];
	ns[i] = '\0';
	if (f == 1)
		free(s);
	return (ns);
}