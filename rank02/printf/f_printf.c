#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

int ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int ft_putstr(const char *s)
{
	int i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

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
	int len = 0;
	char *ns;

	len = ft_strlen(s);
	ns = (char *)malloc(1 * (len + 1));
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

char *ft_itoa_base(unsigned int nb, int base)
{
	int digit = 0;
	char *s;
	unsigned int num;
	num = nb;
	if (nb == 0)
		return (ft_strdup("0"));
	while (num != 0)
	{
		digit++;
		num /= base;
	}
	s = (char *)malloc(1 * digit + 1);
	if (s == NULL)
		return (NULL);
	s[digit--] = '\0';
	while (nb != 0)
	{
		if (nb % base < 10)
			s[digit--] = (nb % base) + 48;
		else
			s[digit--] = (nb % base) + 87;
		nb /= base;
	}
	return (s);
}

char *ft_itoa(int nb)
{
	int digit = 0;
	char *s;
	int neg = 0;
	int num;

	num = nb;
	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	if (nb < 0)
	{
		neg = -1;
		nb *= neg;
		num *= neg;
		digit++;
	}
	while (nb != 0)
	{
		digit++;
		nb /= 10;
	}
	s = (char *)malloc(1 * digit + 1);
	if (s == NULL)
		return (NULL);
	s[digit--] = '\0';
	while (num != 0)
	{
		s[digit--] = (num % 10) + '0';
		num /= 10;
	}
	if (neg == -1)
		s[digit] = '-';
	return (s);

}



int ft_print_hex(unsigned int nb)
{
	char *s;
	int cnt = 0;
	s = ft_itoa_base(nb, 16);
	cnt += ft_putstr(s);
	free(s);
	return (cnt);
}
int ft_print_int(int nb)
{
	char *s;
	int cnt = 0;
	s = ft_itoa(nb);
	cnt += ft_putstr(s);
	free(s);
	return (cnt);
}

int ft_handle_output(int type, va_list args)
{
	int cnt = 0;
	if (type == 'x')
		cnt += ft_print_hex(va_arg(args, unsigned int));
	else if (type == 's')
		cnt += ft_putstr(va_arg(args, char *));
	else if (type == 'd')
		cnt += ft_print_int(va_arg(args, int));
	else
		cnt += ft_putchar(type);
	return (cnt);
}

int ft_handle_input(va_list args, char *s)
{
	int cnt = 0;
	int i = 0;
	int type;

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
			else
				ft_putchar(s[i]);
		}
		i++;
	}
	return (cnt);
}

int ft_printf(const char *input, ...)
{
	int cnt = 0;
	char *s;
	va_list args;

	s = ft_strdup(input);
	va_start(args, input);
	cnt += ft_handle_input(args, s);
	va_end(args);
	free (s);
	return (cnt);
}

int main()
{
	char *s = "Hello there!";
	int i = -23456;
	unsigned int h = 42;

	ft_printf("%s", s);
	ft_putchar('\n');
	ft_printf("%x", h);
	ft_putchar('\n');
	ft_printf("%d", i);
	ft_putchar('\n');
}