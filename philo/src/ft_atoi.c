/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:19:06 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/23 13:27:18 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		sign;
	ssize_t	result;
	ssize_t	stor;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign *= -1;
	while (ft_isdigit(*str))
	{
		stor = result;
		result = (result * 10) + (*str++ - '0');
		if (stor != (result / 10) && sign == 1)
			return (-1);
	}
	return (result * sign);
}
