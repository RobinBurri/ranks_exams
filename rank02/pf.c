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

int ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int ft_putstr(char *s)
{
	int i = 0;
	int cnt = 0;
	while (s[i])
	{
		cnt += ft_putchar(s[i]);
		i++;
	}
	return (cnt);
}

char *ft_strdup(const char *s)
{
	int i = 0;
	char *ns;
	int len;

	len = ft_strlen(s);
	ns = (char *)malloc(len + 1);
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

char *ft_atoi(int nb)
{
	char *ns;
	int digit = 0;
	int num;
	int neg = 1;

	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	if (nb < 0)
	{
		digit++;
		neg = -1;
		num =  nb * -1;
		nb *= -1;
	}
	else
		num = nb;
	while (num != 0)
	{
		digit++;
		num /= 10;
	}
	ns = (char *)malloc(digit + 1);
	if (ns == NULL)
		return (NULL);
	ns[digit] = '\0';
	digit--;
	while (nb != 0)
	{
		ns[digit] = (nb % 10) + '0';
		digit--;
		nb /= 10;
	}
	if (neg == -1)
		ns[digit] = '-';
	return (ns);
}

char *ft_atoi_base(unsigned int nb, int base)
{
	int i = 0;
	char *ns;
	int digit = 0;
	unsigned int num;
	int neg = 1;

	if (nb == 0)
		return (ft_strdup("0"));
	num = nb;
	while (num != 0)
	{
		digit++;
		num /= base;
	}
	ns = (char *)malloc(digit + 1);
	if (ns == NULL)
		return (NULL);
	ns[digit--] = '\0';
	while (nb != 0)
	{
		if ((nb % base) < 10)
			ns[digit--] = (nb % base) + '0';
		else if ((nb % base) > 9)
			ns[digit--] = (nb % base) + 87;
		nb /= base;
	}
	return (ns);
}

int ft_putx(unsigned int nb)
{
	int cnt = 0;
	char *s;
	s = ft_atoi_base(nb, 16);
	cnt += ft_putstr(s);
	free(s);
	return (cnt);	
}

int ft_putd(int nb)
{
	int cnt = 0;
	char *s;
	s = ft_atoi(nb);
	cnt += ft_putstr(s);
	free(s);
	return (cnt);	
}

int ft_handle_output(int type, va_list args)
{
	int cnt = 0;
	if (type == 's')
		cnt += ft_putstr(va_arg(args, char *));
	else if (type == 'x')
		cnt += ft_putx(va_arg(args, unsigned int));
	else if (type == 'd')
		cnt += ft_putd(va_arg(args, int));
	return (cnt);
}

int ft_handle_input(va_list args, char *s)
{
	int i = 0;
	int type;
	int cnt = 0;
	while (s[i])
	{
		if (s[i] != '%')
			cnt += ft_putchar(s[i]);
		else if (s[i] == '%' && s[i + 1])
		{
			i++;
			if (s[i] == 'x' || s[i] == 's' || s[i] == 'd')
			{
				type = s[i];
				cnt += ft_handle_output(type, args);
			}
		}
		else
			cnt += ft_putchar(s[i]);
		i++;
	}	
	return (cnt);
}

int ft_printf(const char *s, ...)
{
	int cnt;
	va_list args;
	char *ns;
	ns = ft_strdup(s);
	va_start(args, s);
	cnt += ft_handle_input(args, ns);
	va_end(args);
	free(ns);
	return (cnt);
}


int main()
{
	// char *s = "arrive";
	int i = -1235;
	int x = 42;

	// ft_printf("%s\n", s);
	ft_printf("%d\n", i);
	ft_printf("%x\n", x);
}