#include <stdarg.h>
#include <stdlib.h>

int	ft_srtlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char *ft_strdup(char *s)
{
	int len;
	char *ns;
	int i;

	len = ft_strlen(s);
	ns = (char *)malloc(1 * (len + 1));
	if (!ns)
		return (NULL);
	while (s[i])
	{
		ns[i] = s[i];
		i++;
	}
	ns[i] = '\0';
	return (ns);
}

int ft_handle_input(const char *str, va_list args)
{
	int	type;
	int	count;
	int	i;

	while(str[i])
	{
		if (str[i] != '%')
			count += ft_putchar(str[i]);
		else if (str[i] == '%' && str[i + 1])
		{
			i++;
			type = str[i];
			if (str[i] == 's' || str[i] == 'x' || str[i] == 'd')
				count += ft_handle_output(type, args);
			else
				count += ft_putchar(str[i]);
		}
		i++;
	}
	return (count);
}

int	ft_printf(const char *input, ...)
{
	va_list args;
	int res;
	char *str;

	str = ft_strdup(input);
	if (!str)
		return (-1);
	va_start(args, input);
	res += ft_handle_input(str, args);
	va_end(args);
	free(str);
	return (res);
}
