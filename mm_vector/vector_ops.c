/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 04:15:17 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/01 11:12:31 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mm_vector.h"

void	vec_iter(t_vec *vec, void f(void *))
{
	size_t	i;

	i = 0;
	while (i < vec->len)
	{
		f(vec->v + (i * vec->ele_size));
		i++;
	}
}

void	*vec_pop(t_vec *vec)
{
	void	*item;

	if (vec->len == 0)
		return (NULL);
	item = malloc(vec->ele_size);
	if (item == NULL)
		return (NULL);
	if (!ft_memcpy(item, vec_get(vec, vec->len - 1), vec->ele_size))
		return (NULL);
	vec->len--;
	if (vec->len < vec->cap / 4)
		vec_resize(vec, vec->cap / 2);
	return (item);
}

t_vec	*vec_del(t_vec *vec, size_t i)
{
	if (i >= vec->len)
		return (NULL);
	if (i < vec->len - 1)
		ft_memcpy(vec->v + (i * vec->ele_size),
			vec->v + ((i + 1) * vec->ele_size),
			((vec->len - (i + 1)) * (vec->ele_size)));
	vec->len--;
	if (vec->len < vec->cap / 4)
		vec_resize(vec, vec->cap / 2);
	return (vec);
}

size_t	vec_find(t_vec *vec, void *item)
{
	size_t	i;

	i = 0;
	while (i < vec->len)
	{
		if (ft_memcmp(vec_get(vec, i), item, vec->ele_size) == 0)
			return (i);
	}
	return ((size_t)-1);
}

void	vec_debug(t_vec *vec, int vec_type)
{
	size_t	i;

	if (vec == NULL)
	{
		ft_printf("vec is NULL\n");
		return ;
	}
	ft_printf("v: ");
	i = 0;
	while (i < vec->len)
	{
		if (vec_type == VEC_STR)
			ft_printf("\n\t%s", *(char **)vec_get(vec, i));
		if (vec_type == VEC_INT)
			ft_printf("    %i", *(int *)vec_get(vec, i));
		if (vec_type == VEC_CHAR)
			ft_printf("    %c", (char *)vec_get(vec, i));
		i++;
	}
	ft_printf("\nele_size: %u", (unsigned int)vec->ele_size);
	ft_printf("\nlen: %u", (unsigned int)vec->len);
	ft_printf("\ncap: %u\n", (unsigned int)vec->cap);
}
