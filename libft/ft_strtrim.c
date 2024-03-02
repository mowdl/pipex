/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:11:58 by mel-meka          #+#    #+#             */
/*   Updated: 2023/11/11 23:21:36 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 && is_in_set(*s1, set))
		s1++;
	len = ft_strlen(s1);
	if (len == 0)
		return (ft_substr(s1, 0, 0));
	len--;
	while (s1[len] && is_in_set(s1[len], set))
		len--;
	return (ft_substr(s1, 0, len + 1));
}
