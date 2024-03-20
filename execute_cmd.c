/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 21:11:01 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/20 01:15:07 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_cmd(t_pipex *pipex, char *cmd)
{
	pipex->cmd_args = ft_split(cmd, ' ');
	if (pipex->cmd_args == NULL)
		pipex_error(NULL);
}

char	**get_path_var(char **envp)
{
	char	*path_str;
	char	**arr;

	path_str = NULL;
	while (*envp)
	{
		if ((*envp)[0] == 'P' && (*envp)[1] == 'A' && (*envp)[2] == 'T' && (*envp)[3] == 'H')
		{
			path_str = *envp;
			break ;
		}
		envp++;
	}
	if (path_str == NULL)
		return (NULL);
	arr = ft_split(path_str, ':');
	if (arr == NULL)
		pipex_error(NULL);
	return (arr);
}

char	*get_cmd_path(char **path_var, char *cmd)
{
	char	*str;
	char	*tmp;

	while (*path_var)
	{
		str = ft_strjoin(*path_var, "/");
		if (str == NULL)
			pipex_error(NULL);
		tmp = ft_strjoin(str, cmd);
		free(str);
		if (tmp == NULL)
			pipex_error(NULL);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		path_var++;
	}
	return (NULL);
}

void	execute_command(t_pipex *pipex, char *cmd)
{
	char	**path_var;
	char	*cmd_path;

	parse_cmd(pipex, cmd);
	cmd = pipex->cmd_args[0];
	path_var = get_path_var(pipex->envp);
	cmd_path = get_cmd_path(path_var, cmd);
	if (cmd_path == NULL)
	{
		cmd_path = cmd;
		if (access(cmd_path, X_OK) != 0)
			pipex_error(cmd_path);
	}
	execve(cmd_path, pipex->cmd_args, pipex->envp);
	pipex_error(NULL);
}

