/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:59:15 by mel-meka          #+#    #+#             */
/*   Updated: 2024/02/28 03:32:28 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	digits_hex(unsigned long n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		i++;
		n /= 16;
	}
	return (i);
}

void	hex(unsigned long n, char *str)
{
	if (n < 16)
	{
		ft_putchar(str[n]);
	}
	else
	{
		hex(n / 16, str);
		hex(n % 16, str);
	}
}

int	ft_put_hex(unsigned long n, int upper, int pointer)
{
	char	*str;

	if (upper)
		str = "0123456789ABCDEF";
	else
		str = "0123456789abcdef";
	if (pointer)
		if (write(1, "0x", 2) == -1)
			return (-1);
	hex(n, str);
	return (digits_hex(n) + (pointer != 0) * 2);
}
