/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:42:56 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/12 16:50:34 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdarg.h>
#include <unistd.h>

size_t ft_strlen(const char *s);
void ft_putnbr_fd(int fd, int n, int *counter);
void ft_put_unsigned_nbr_fd(int fd, unsigned int n, int *counter);
void ft_puthex_fd(int fd, size_t n, const char *base, int *counter);
void ft_putaddress_fd(int fd, size_t address, int *counter);
int ft_putchar_fd(int fd, char c);
int ft_putstr_fd(int fd, char *s);
int ft_fprintf(int fd, const char *format, ...);

#endif
