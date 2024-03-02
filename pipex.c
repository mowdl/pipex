/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 05:47:09 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/01 10:49:32 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "mm_vector.h"

void f2(void *item)
{
	*(int *)item *= 2;
}

int	main()
{
	t_vec *vec;

	vec = vec_new(sizeof(int));
	for (int i = 0; i < 10; i++)
	{
		if (!vec_push(vec, &i))
			ft_printf("err\n");
	}
	vec_iter(vec, f2);
	int *a = vec_pop(vec);
	free(a);
	vec_del(vec, 8);
	vec_debug(vec, VEC_INT);
	free(vec->v);
	free(vec);
}
