#include <stdio.h>
#include "ft_atoi.c"
#include <stdlib.h>


static int	ft_len(long int n)
{
	int len;
	int a;

	len = 0;
	a = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		a = 1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	if (a == 1)
		len++;
	return (len);
}

static char	*ft_fill(int i, int a, char *str, long int nb)
{
	while (i >= a)
	{
		str[i--] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (str);
}

char		*ft_itoa(int n)
{
	char		*str;
	int			i;
	long int	nb;
	int			a;
	int			len;

	nb = n;
	i = 0;
	a = 0;
	len = ft_len(nb);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
		a = 1;
	}
	i = (len) - 1;
	str = ft_fill(i, a, str, nb);
	str[len] = '\0';
	return (str);
}


static void		set_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

int main(void)
{
    char str[200];

	*(str + 2) = *ft_itoa(14);
	*(str + 10) = *ft_itoa(20);
	printf ("str = '%s'\n", str);
}
