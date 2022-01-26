#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int ft_strlen(const char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

char 	*ft_strdup(const char *s)
{
	int len;
	int i = 0;
	char *ns;

	len = ft_strlen(s);
	ns = (char *)malloc(len + 1);
	if (!ns)
		return (NULL);
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
	return write(1, &c, 1);
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

char *ft_atoi(int nbr)
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
		nbr /= 10;
		dt++;	
	}
	ns = (char *)malloc(dt + 1);
	if (!ns)
		return (NULL);
	ns[dt--] = '\0';
	while (num != 0)
	{
		ns[dt--] = num % 10 + '0';
		num /= 10;
	}
	if (sign == -1)
		ns[dt] = '-';
	return (ns);
}

char *ft_atoi_base(unsigned int nbr, int base)
{
	int dt = 0;;
	int num;
	char *ns;

	if (nbr == 0)
		return (ft_strdup("0"));
	num = nbr;
	while (nbr != 0)
	{
		nbr /= base;
		dt++;	
	}
	ns = (char *)malloc(dt + 1);
	if (!ns)
		return (NULL);
	ns[dt--] = '\0';
	while (num != 0)
	{
		if ((num % base) < 10)
			ns[dt] = (num % base) + '0';
		else
			ns[dt] = (num % base) + 87;
		num /= base;
		dt--;
	}
	return (ns);
}

int ft_putx(unsigned int nbr)
{
	char *ns;
	int cnt = 0;
	ns = ft_atoi_base(nbr, 16);
	cnt += ft_putstr(ns);
	free(ns);
	return (cnt);
}

int ft_putd(int nbr)
{
	char *ns;
	int cnt = 0;
	ns = ft_atoi(nbr);
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
int	ft_printf(const char *s, ...)
{
	int cnt = 0;
	char *ns;
	va_list args;

	ns = ft_strdup(s);
	if (!ns)
		return (-1);
	va_start(args, s);
	cnt += ft_handle_input(args, ns);
	va_end(args);
	free(ns);
	return (cnt);
}

int main()
{
//	int a = -42;
	unsigned int h = 42;
//	char *s = "hello";
	// char *v = NULL;

//	ft_printf("%d\n", a);
	ft_printf("%x\n", h);
//	ft_printf("%s\n", s);
	// ft_printf("%s\n", v);
	return (0);
}
