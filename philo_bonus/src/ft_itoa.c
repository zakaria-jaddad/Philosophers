/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:15:23 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/13 20:15:50 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*s++)
		length++;
	return (length);
}

static int	count_digit(int i)
{
	int	counter;

	counter = 1;
	while (i / 10)
	{
		counter++;
		i /= 10;
	}
	return (counter);
}

static void	reverse(char *s)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j)
	{
		tmp = s[j];
		s[j--] = s[i];
		s[i++] = tmp;
	}
	s[ft_strlen(s)] = 0;
}

static int	check_sign(long *long_n, int *sign)
{
	if (*long_n < 0)
	{
		*long_n *= -1;
		*sign = -1;
	}
	if (*sign == -1)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	int		n_length;
	int		i;
	int		sign;
	long	long_n;
	char	*ptr;

	long_n = n;
	n_length = count_digit(long_n);
	sign = 1;
	i = 0;
	ptr = (char *) malloc(n_length + 1 + check_sign(&long_n, &sign));
	if (ptr == NULL)
		return (NULL);
	while (n_length--)
	{
		ptr[i++] = (long_n % 10) + '0';
		long_n /= 10;
	}
	if (sign == -1)
		ptr[i++] = '-';
	ptr[i] = 0;
	reverse(ptr);
	return (ptr);
}
