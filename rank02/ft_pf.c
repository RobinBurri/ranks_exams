#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

int ft_strlen(const char *s)
{
	int i = 0;
	if (s == 0)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int ft_putstr(char *s)
{
	int i = 0;
	while (s[i])
		ft_putchar(s[i++]);
	return (i);
}

char *ft_strdup(const char *s)
{
	int i = 0;
	int len;
	char *ns;

	len = ft_strlen(s);
	ns = (char *)malloc(len + 1);
	if (ns == 0)
		return (0);
	while (s[i])
	{
		ns[i] = s[i];
		i++;
	}
	ns[i] = 0;
	return (ns);
}

char *ft_atoi(int nbr)
{
	char *ns;
	int dt = 0;
	int num;
	int sign = 1;

	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	if (nbr < 0)
	{
		dt++;
		sign = -1;
		nbr *= sign;
	}
	num = nbr;
	while (num != 0)
	{
		num /= 10;
		dt++;
	}
	ns = (char *)malloc(dt + 1);
	ns[dt--] = 0;
	while (nbr != 0)
	{
		ns[dt--] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (sign == -1)
		ns[dt] = '-';
	return (ns);
}

char *ft_atoi_base(unsigned int nbr, int base)
{
	char *ns;
	int dt = 0;
	int num;


	if (nbr == 0)
		return (ft_strdup("0"));
	num = nbr;
	while (num != 0)
	{
		num /= base;
		dt++;
	}
	ns = (char *)malloc(dt + 1);
	ns[dt--] = 0;
	while (nbr != 0)
	{
		if (nbr % base < 10)
			ns[dt--] = nbr % base + '0';
		else
			ns[dt--] = nbr % base + 87;
			
		nbr /= base;
	}
	return (ns);
}

int ft_putd(int nbr)
{
	int cnt = 0;
	char *tmp;
	tmp = ft_atoi(nbr);
	cnt += ft_putstr(tmp);
	free(tmp);
	return (cnt);
}

int ft_putx(unsigned int nbr)
{
	int cnt = 0;
	char *tmp;
	tmp = ft_atoi_base(nbr, 16);
	cnt += ft_putstr(tmp);
	free(tmp);
	return (cnt);
}

int ft_handle_output(va_list args, int type)
{
	int cnt = 0;
	if (type == 's')
		cnt += ft_putstr(va_arg(args, char *));
	else if (type == 'd')
		cnt += ft_putd(va_arg(args, int));
	else
		cnt += ft_putx(va_arg(args, unsigned int));
	return (cnt);
}

int ft_handle_input(va_list args, char *s)
{
	int i = 0;
	int cnt = 0;
	int type;
	while (s[i])
	{
		if (s[i] != '%')
			cnt += ft_putchar(s[i]);
		else if (s[i] == '%' && s[i + 1])
		{
			i++;
			type = s[i];
			if (type == 's' || type == 'x' || type == 'd')
				cnt += ft_handle_output(args, type);
			else
				cnt += ft_putchar(s[i]);
		}
		i++;
	}
	return (cnt);
}

int ft_printf(const char *s, ...)
{
	int cnt = 0;
	va_list args;
	char *tmp;
	tmp = ft_strdup(s);
	if (tmp == 0)
		return (0);
	va_start(args, s);
	cnt += ft_handle_input(args, tmp);
	va_end(args);
	free(tmp);
	return (cnt);
}

int main(void)
{
	int i = -42;
	int hex = 42;
	char *s = "hello";
	ft_printf("%s\n", s);
	ft_printf("%d\n", i);
	ft_printf("%x\n", hex);
	return (0);
}