/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:15:14 by mel-meka          #+#    #+#             */
/*   Updated: 2023/11/11 17:15:15 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*r;
	char	ch;
	size_t	len;
	size_t	i;

	ch = c;
	len = ft_strlen(s);
	i = 0;
	r = 0;
	while (i < len)
	{
		if (s[i] == ch)
			r = ((char *)(s + i));
		i++;
	}
	if (ch == '\0')
		return ((char *)(s + i));
	return (r);
}
