/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:11:31 by mel-meka          #+#    #+#             */
/*   Updated: 2023/11/11 17:12:42 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	unsigned int	i;
	char			*r;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	r = ft_calloc(len + 1, sizeof(char));
	if (r == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		r[i] = f(i, s[i]);
		i++;
	}
	return (r);
}
