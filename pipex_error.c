/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:17:38 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/20 05:15:49 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_error(char *str, int v)
{
	char	*tmp;
	char	*tmp2;

	if (str == NULL)
	{
		perror(get_pipex()->av[0]);
	}
	else
	{
		tmp = ft_strjoin(get_pipex()->av[0], ": ");
		if (tmp != NULL)
		{
			tmp2 = ft_strjoin(tmp, str);
			perror(tmp2);
			free(tmp2);
			free(tmp);
		}
		else
			perror(NULL);
	}
	exit(v);
}
