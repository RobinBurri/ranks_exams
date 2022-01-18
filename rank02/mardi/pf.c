#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

int ft_strlen(const char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int i = 0;
	if (!s)
		s = ("(null)");
	while (s[i])
		ft_putchar(s[i++]);
	return (i);
}

char *ft_strdup(const char *s)
{
	int i = 0;
	char *ns;
	int len = ft_strlen(s);
	ns = (char *)malloc(len + 1);
	if (!ns)
		return (0);
	while (s[i])
	{
		ns[i] = s[i];
		i++;
	}
	ns[i] = 0;
	return (ns);
}

char *ft_itoa_base(unsigned int nbr, int base)
{
	int dt = 0;
	int num;
	char *ns;

	if (nbr == 0)
		return (ft_strdup("0"));
	num = nbr;
	while (nbr != 0)
	{
		dt++;
		nbr /= base;
	}
	ns = (char *)malloc(dt + 1);
	if (!ns)
		return (0);
	ns[dt--] = 0;
	while (num != 0)
	{
		if (num % base < 10)
			ns[dt--] = num % base + '0';
		else
			ns[dt--] = num % base + 87;
		num /= base;
	}
	return (ns);
}

char *ft_itoa(int nbr)
{
	int dt = 0;
	int sign = 1;
	int num;
	char *ns;

	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	if (nbr < 0)
	{
		sign = -1;
		dt++;
		nbr *= sign;
	}
	num = nbr;
	while (nbr != 0)
	{
		dt++;
		nbr /= 10;
	}
	ns = (char *)malloc(dt + 1);
	if (!ns)
		return (0);
	ns[dt--] = 0;
	while (num != 0)
	{
		ns[dt--] = num % 10 + '0';
		num /= 10;
	}
	if (sign == -1)
		ns[dt] = '-';
	return (ns);
}


int ft_putx(unsigned int nbr)
{
	int c = 0;
	char *ns;
	ns = ft_itoa_base(nbr, 16);
	c += ft_putstr(ns);
	free (ns);
	return (c);
}

int ft_putd(int nbr)
{
	int c = 0;
	char *ns;
	ns = ft_itoa(nbr);
	c += ft_putstr(ns);
	free (ns);
	return (c);
}

int ft_h_output(va_list args, int t)
{
	int c = 0;
	if (t == 's')
		c += ft_putstr(va_arg(args, char *));
	else if (t == 'd')
		c += ft_putd(va_arg(args, int));
	else if (t == 'x')
		c += ft_putx(va_arg(args, unsigned int));
	return (c);
}

int ft_h_input(va_list args, char *s)
{
	int cnt = 0;
	int i = 0;
	int t;
	while (s[i])
	{
		if (s[i] != '%')
			cnt += ft_putchar(s[i]);
		else if (s[i] == '%' && s[i + 1])
		{
			i++;
			t = s[i];
			if (t == 's' || t == 'x' || t == 'd')
				cnt += ft_h_output(args, t);
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
	char *ns;
	va_list args;

	va_start(args, s);
	ns = ft_strdup(s);
	if (!ns)
		return (-1);
	cnt += ft_h_input(args, ns);
	va_end(args);
	free(ns);
	return (cnt);
}

int main()
{
	int a = -42;
	int h = 42;
	char *s = "hello";
	char *v = NULL;

	ft_printf("%d\n", a);
	ft_printf("%x\n", h);
	ft_printf("%s\n", s);
	ft_printf("%s\n", v);
}
