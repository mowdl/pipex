/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:10:49 by mel-meka          #+#    #+#             */
/*   Updated: 2023/11/11 17:10:51 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (src_len >= dstsize)
	{
		if (dstsize > 0)
		{
			ft_memcpy(dst, src, dstsize);
			dst[dstsize - 1] = '\0';
		}
	}
	else
		ft_memcpy(dst, src, src_len + 1);
	return (src_len);
}
