/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_putstr_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:43:03 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/26 18:04:27 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_fprintf_putstr_fd(int fd, char *s)
{
	if (s == NULL)
		return (write(fd, "(null)", 6));
	return (write(fd, s, ft_fprintf_strlen(s)));
}
