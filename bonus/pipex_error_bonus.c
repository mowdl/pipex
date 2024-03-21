/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:17:38 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/20 05:15:49 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**free_arr(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(arr);
	return (NULL);
}

void	pipex_clean(t_pipex *pipex)
{
	if (pipex->cmd_args)
		free_arr(pipex->cmd_args);
	if (pipex->path_var)
		free_arr(pipex->path_var);
	if (pipex->pids)
		free(pipex->pids);
}

void	pipex_cmd_not_found(char *cmd)
{
	if (*cmd != '\0' && !write(2, cmd, ft_strlen(cmd)))
		pipex_error("write", 1);
	if (!write(2, ": command not found\n", 20))
		pipex_error("write", 1);
	pipex_clean(get_pipex());
	exit(127);
}

void	pipex_error(char *str, int v)
{
	char	*tmp;
	char	*tmp2;

	pipex_clean(get_pipex());
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
