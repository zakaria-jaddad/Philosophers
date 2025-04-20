/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:11:46 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/12 16:48:16 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_fprintf.h"

void ft_putaddress_fd(int fd, size_t address, int *counter) {
  *counter += ft_putstr_fd(fd, "0x");
  ft_puthex_fd(fd, address, "0123456789abcdef", counter);
}
