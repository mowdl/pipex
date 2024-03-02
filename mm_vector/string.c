/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 04:15:17 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/01 11:26:10 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mm_vector.h"

t_string	*string_new(char *str)
{
	t_vec	*vec;

	vec = vec_new();
	if (vec == NULL)
		return (NULL);
	vec->v = ft_strdup(str);
	if (ve->v == NULL)
		return (NULL);
	vec->ele_size = sizeof(char);
	vec->len = ft_strlen(str);
	vec->cap = vec->len + 1;
}
