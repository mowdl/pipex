/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:53:37 by mel-meka          #+#    #+#             */
/*   Updated: 2023/11/15 22:46:49 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*r;

	if (size != 0 && count >= SIZE_MAX / size)
		return (NULL);
	r = malloc(count * size);
	if (r == 0)
		return (r);
	ft_bzero(r, count * size);
	return (r);
}
