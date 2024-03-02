/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 04:15:17 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/01 11:03:21 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mm_vector.h"

t_vec	*vec_new(size_t element_size)
{
	t_vec	*vec;

	vec = malloc(sizeof(t_vec));
	if (!vec)
		return (vec);
	vec->ele_size = element_size;
	vec->len = 0;
	vec->cap = 0;
	return (vec);
}

t_vec	*vec_resize(t_vec *vec, size_t new_cap)
{
	void	*new_v;

	new_v = malloc(new_cap * vec->ele_size);
	if (new_v == NULL)
		return (NULL);
	if ((vec->cap != 0) && ft_memcpy(new_v,
			vec->v,
			vec->len * vec->ele_size) == NULL)
	{
		free(new_v);
		return (NULL);
	}
	if (vec->cap != 0)
		free(vec->v);
	vec->v = new_v;
	vec->cap = new_cap;
	return (vec);
}

void	*vec_get(t_vec *vec, size_t i)
{
	if (i > vec->len)
		return (NULL);
	return (vec->v + i * vec->ele_size);
}

t_vec	*vec_push(t_vec *vec, void *ele)
{
	if ((vec->len + 1) > vec->cap)
		if (vec_resize(vec, vec->cap * 2 + (vec->cap == 0)) == NULL)
			return (NULL);
	if (ft_memcpy(vec->v + vec->len * vec->ele_size,
			ele,
			vec->ele_size * 1) == NULL)
		return (NULL);
	vec->len++;
	return (vec);
}

t_vec	*vec_insert(t_vec *vec, void *ele, size_t i)
{
	if ((vec->len + 1) > vec->cap)
		if (vec_resize(vec, vec->cap * 2 + (vec->cap == 0)) == NULL)
			return (NULL);
	if (ft_memcpy(vec->v + i * vec->ele_size,
			vec->v + (i + 1) * vec->ele_size,
			(vec->len - i) * vec->ele_size) == NULL)
		return (NULL);
	if (ft_memcpy(vec->v + i * vec->ele_size, ele, vec->ele_size * 1) == NULL)
		return (NULL);
	return (vec);
}
