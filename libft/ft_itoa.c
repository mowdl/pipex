/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:54:31 by mel-meka          #+#    #+#             */
/*   Updated: 2023/11/11 16:54:35 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits_count(int n)
{
	int	c;

	if (n == 0)
		return (1);
	c = 0;
	while (n != 0)
	{
		n /= 10;
		c++;
	}
	return (c);
}

static char	*rev_str(char *s, int len)
{
	int		i;
	char	tmp;

	i = 0;
	while (i < len / 2)
	{
		tmp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = tmp;
		i++;
	}
	return (s);
}

static void	set_digits(char *s, int n, int digits)
{
	int	i;
	int	sign;

	if (n < 0)
		sign = -1;
	else
		sign = 1;
	i = 0;
	while (i < digits)
	{
		s[i] = '0' + (n % 10) * sign;
		n /= 10;
		i++;
	}
}

char	*ft_itoa(int n)
{
	int		digits;
	int		is_neg;
	char	*s;

	digits = digits_count(n);
	is_neg = 0;
	if (n < 0)
		is_neg = 1;
	s = ft_calloc(digits + is_neg + 1, sizeof(char));
	if (s == NULL)
		return (NULL);
	set_digits(s, n, digits);
	if (is_neg)
		s[digits] = '-';
	s[digits + is_neg] = '\0';
	return (rev_str(s, digits + is_neg));
}
