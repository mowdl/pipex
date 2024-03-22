/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 04:15:52 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/01 11:04:02 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MM_VECTOR_H
# define MM_VECTOR_H

# include "libft.h"
# include "ft_printf.h"
# include <stdlib.h>

# define VEC_INT	0
# define VEC_CHAR	1
# define VEC_STR	2

typedef struct s_vec
{
	void	*v;
	size_t	ele_size;
	size_t	len;
	size_t	cap;
}			t_vec;

t_vec	*vec_new(size_t element_size);
void	*vec_get(t_vec *vec, size_t i);
t_vec	*vec_push(t_vec *vec, void *ele);
void	vec_debug(t_vec *vec, int vec_type);
t_vec	*vec_resize(t_vec *vec, size_t new_cap);
t_vec	*vec_insert(t_vec *vec, void *ele, size_t i);
void	vec_iter(t_vec *vec, void f(void *));
void	*vec_pop(t_vec *vec);
t_vec	*vec_del(t_vec *vec, size_t i);
size_t	vec_find(t_vec *vec, void *item);

#endif
