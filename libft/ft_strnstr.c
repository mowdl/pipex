/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:11:45 by mel-meka          #+#    #+#             */
/*   Updated: 2023/11/12 00:31:26 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_segfault(void)
{
	char	*ptr;

	ptr = 0;
	*ptr = 0;
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;
	size_t	i;

	if (needle == NULL)
		ft_segfault();
	if (len == 0 && haystack == NULL)
		return ((char *)haystack);
	if (haystack == NULL)
		ft_segfault();
	nlen = ft_strlen(needle);
	if (nlen == 0)
		return ((char *)haystack);
	if (len < nlen)
		return (0);
	i = 0;
	while (i < len - nlen + 1 && haystack[i] != '\0')
	{
		if (ft_strncmp(haystack + i, needle, nlen) == 0)
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}
