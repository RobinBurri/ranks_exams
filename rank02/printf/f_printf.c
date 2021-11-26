#include <stdlib.h>
#include <sddarg.h>

int ft_putchar(char c)
{
	write(1, c, 1);
	return (1);
}

int ft_putstr(char *s)
{
	int i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

ft_strdup(char *s)
{
	char *ns;
	int i = 0;
	int len;

	len = strlen(input);
	ns  = (char *)malloc(1 * (len + 1))
	if (ns == NULL)
		return (NULL);
	while (s[i])
	{
		ns[i] = s[i];
		i++;
	}
	ns[i] = '\0';
	return (ns);
}

int printhex(unsigned int num)
{

}

int printint(int num)
{

}

int ft_handle_output(int type, va_list args)
{
	int cnt = 0;
	if (type == 'd')
		cnt += ft_printint(va_arg(args, int));
	else if (type == 'x')
		cnt += ft_printhex(va_arg(args, unsigned int));
	else if (type == 's')
		cnt += ft_putstr(va_arg(args, char *));
	return (cnt);	
}


int ft_handle_input(char *str, va_list args)
{
	int i = 0;
	int type = 0;
	int cnt = 0;
	while (str[i])
	{
		if (str[i] != '%')
			cnt += ft_putchar(str[i]);
		else if (str[i] == '%' && str[i + 1])
		{
			i++;
			if (str[i] == 's' || str[i] == 'x' || str[i] == 'd')
			{
				type = str[i];
				cnt += ft_handle_output(type, args);
			}
			else
				cnt += ft_putchar(str[i]);
		}
		i++;
	}
	return (cnt);
}

int ft_printf(const char *input, ...)
{
	char *str;
	int cnt;
	va_list args;

	cnt = 0;
	va_start(args, input);
	cnt += ft_handle_input(str, args);
	va_stop(args);
	free(str);
	return (cnt);
}
