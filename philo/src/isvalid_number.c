/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isvalid_number.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:54:47 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/08 16:06:04 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	isvalid_number(char *element)
{
	int	digit;
	int	sign;

	digit = 0;
	sign = 0;
  if (*element == 0)
    return (false);
	while (*element)
	{
		if (*element == '+')
		{
			if ((digit == 0 && sign == 0) && *(element + 1) != 0)
			{
				sign = (element++, digit++, sign + 1);
				continue ;
			}
			else
				return (0);
		}
		if (ft_isdigit(*element) == false)
			return (false);
		element++;
		digit++;
	}
	return (true);
}
