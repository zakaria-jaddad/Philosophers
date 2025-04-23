/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:28:29 by zajaddad          #+#    #+#             */
/*   Updated: 2024/11/28 15:13:09 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_fprintf.h"

size_t	ft_fprintf_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*s++)
		length++;
	return (length);
}
