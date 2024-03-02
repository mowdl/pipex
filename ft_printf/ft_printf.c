/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:56:10 by mel-meka          #+#    #+#             */
/*   Updated: 2023/11/26 16:31:09 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_switch(const char *str, int i, va_list ptr)
{
	int	r;

	r = 0;
	if (str[i + 1] == 'd' || str[i + 1] == 'i')
		r += put_int(va_arg(ptr, int));
	else if (str[i + 1] == 'u')
		r += put_unsigned_int(va_arg(ptr, unsigned int));
	else if (str[i + 1] == 'c' && (++r))
		ft_putchar(va_arg(ptr, int));
	else if (str[i + 1] == 'x')
		r += ft_put_hex(va_arg(ptr, unsigned int), 0, 0);
	else if (str[i + 1] == 'X')
		r += ft_put_hex(va_arg(ptr, unsigned int), 1, 0);
	else if (str[i + 1] == 'p')
		r += ft_put_hex((unsigned long)va_arg(ptr, void *), 0, 1);
	else if (str[i + 1] == 's')
		r += ft_put_str(va_arg(ptr, char *));
	else if (str[i + 1] == '%')
	{
		ft_putchar('%');
		r++;
	}
	return (r);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		r;
	va_list	ptr;

	va_start(ptr, str);
	r = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_putchar(str[i]);
			r++;
		}
		else if (str[i + 1] != '\0')
		{
			r += ft_printf_switch(str, i, ptr);
			i++;
		}
		i++;
	}
	return (r);
}
