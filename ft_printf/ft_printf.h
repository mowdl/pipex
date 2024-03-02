/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:01:05 by mel-meka          #+#    #+#             */
/*   Updated: 2023/11/26 16:01:50 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);

void	ft_putchar(char c);

int		digits(long n);
int		put_int(int n);
int		put_unsigned_int(unsigned int n);
int		ft_put_str(char *s);
int		ft_put_hex(unsigned long n, int upper, int pointer);

#endif // !FT_PRINTF_H
