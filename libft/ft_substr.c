/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:12:08 by mel-meka          #+#    #+#             */
/*   Updated: 2023/11/11 22:17:35 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*empty_str(void)
{
	char	*r;

	r = ft_calloc(sizeof(char), 1);
	if (r == NULL)
	{
		return (NULL);
	}
	*r = '\0';
	return (r);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	s_len;
	size_t	i;

	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (start >= s_len || s_len == 0 || len == 0)
		return (empty_str());
	if (len > s_len - start)
		len = s_len - start;
	r = ft_calloc(sizeof(char), (len + 1));
	if (r == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		r[i] = s[i + start];
		i++;
	}
	r[i] = '\0';
	return (r);
}
