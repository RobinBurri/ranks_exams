#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

int ft_strlen(const char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

char *ft_strdup(const char *s)
{
	int i = 0;
	char *ns;
	if (!s)
		return (NULL);
	int len = ft_strlen(s);
	ns = (char *)malloc(len +1);
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

int ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int ft_putstr(char *s)
{
	int i = 0;
	if (!s)
		s = ("(null)");
	while (s[i])
		ft_putchar(s[i++]);
	return (i);
}

char *ft_itoa(int nbr)
{
	char *ns;
	int dt = 0;
	int sign = 1;
	int num;
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
		return 0;
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

char *ft_itoa_base(unsigned int nbr, int base)
{
	char *ns;
	int dt = 0;
	int num;
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
		return 0;
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

int ft_putd(int nbr)
{
	int cnt = 0;
	char *ns;
	ns = ft_itoa(nbr);
	if (!ns)
		return (-1);
	cnt += ft_putstr(ns);
	free(ns);
	return (cnt);
}

int ft_putx(unsigned int nbr)
{
	int cnt = 0;
	char *ns;
	ns = ft_itoa_base(nbr, 16);
	if (!ns)
		return (-1);
	cnt += ft_putstr(ns);
	free(ns);
	return (cnt);
}

int ft_handle_output(va_list args, int t)
{
	int cnt = 0;
	if (t == 's')
		cnt += ft_putstr(va_arg(args, char *));
	else if (t == 'x')
		cnt += ft_putx(va_arg(args, unsigned int));
	else if (t == 'd')
		cnt += ft_putd(va_arg(args, int));
	return (cnt);
}

int ft_handle_input(va_list args, char *s)
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
		   cnt += ft_handle_output(args, t);
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
	char *ns;
	ns = ft_strdup(s);
	if (!ns)
		return (1);
	va_start(args, s);
	cnt += ft_handle_input(args, ns);
	va_end(args);
	free(ns);
	return (0);
}


int main()
{
	int d = -42;
	int x = 42;
	char *s = "test";
	char *v = NULL;

	ft_printf("%d\n", d);
	ft_printf("%x\n", x);
	ft_printf("%s\n", s);
	ft_printf("%s\n", v);
}
