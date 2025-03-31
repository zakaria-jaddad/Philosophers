/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isvalid_number.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:54:47 by zajaddad          #+#    #+#             */
/*   Updated: 2025/03/29 00:32:34 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (True);
	return (False);
}

t_bool	isvalid_number(char *element)
{
	int	digit;
	int	sign;

	digit = 0;
	sign = 0;
  if (*element == 0)
    return (False);
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
		if (ft_isdigit(*element) == False)
			return (False);
		element++;
		digit++;
	}
	return (True);
}
