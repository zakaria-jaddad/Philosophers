/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:37:46 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/12 16:47:56 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_fprintf.h"

void ft_puthex_fd(int fd, size_t n, const char *base, int *counter) {
  size_t base_len;

  base_len = ft_fprintf_strlen(base);
  if (n >= base_len)
    ft_puthex_fd(fd, (n / base_len), base, counter);
  *counter += ft_putchar_fd(fd, base[n % base_len]);
}
