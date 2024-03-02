/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:29:25 by mel-meka          #+#    #+#             */
/*   Updated: 2023/11/26 16:16:45 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	digits(long n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

void	put_long(long n)
{
	if (n < 0)
	{
		ft_putchar('-');
		put_long(-n);
	}
	else if (n < 10)
	{
		ft_putchar('0' + n);
	}
	else
	{
		put_long(n / 10);
		put_long(n % 10);
	}
}

int	put_int(int n)
{
	put_long(n);
	return (digits(n) + (n < 0));
}

int	put_unsigned_int(unsigned int n)
{
	put_long(n);
	return (digits(n));
}
