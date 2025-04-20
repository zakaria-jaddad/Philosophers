/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned_nbr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:18:15 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/12 16:47:33 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_fprintf.h"

void ft_put_unsigned_nbr_fd(int fd, unsigned int n, int *counter) {
  if (n < 10)
    *counter += ft_putchar_fd(fd, (n + '0'));
  else {
    ft_putnbr_fd(fd, (n / 10), counter);
    *counter += ft_putchar_fd(fd, ((n % 10) + '0'));
  }
}
