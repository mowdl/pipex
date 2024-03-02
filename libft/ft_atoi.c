/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:53:14 by mel-meka          #+#    #+#             */
/*   Updated: 2023/11/16 00:06:39 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static long	will_it_be_larger_than_a_long(long r, long s, const char *str)
{
	r = (r * s) * 10;
	if (s > 0 && r < 0)
		return (LONG_MAX);
	if (s < 0 && r > 0)
		return (LONG_MIN);
	r = r + s * (*str - '0');
	if (s > 0 && r < 0)
		return (LONG_MAX);
	if (s < 0 && r > 0)
		return (LONG_MIN);
	return (0);
}

static long	get_int(const char *str, long s)
{
	long	r;
	char	digits;
	long	err;

	digits = 0;
	r = 0;
	while (*str && ft_isdigit(*str))
	{
		digits++;
		if (digits >= 18)
		{
			err = will_it_be_larger_than_a_long(r, s, str);
			if (err)
				return (err);
		}
		r = r * 10 + (*str - '0');
		str++;
	}
	return (r * s);
}

int	ft_atoi(const char *str)
{
	int	r;
	int	s;

	while (*str != '\0'
		&& (*str == ' ' || *str == '\t' || (*str >= 9 && *str <= 13)))
	{
		str++;
	}
	s = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s = -1;
		str++;
	}
	r = get_int(str, s);
	return (r);
}
