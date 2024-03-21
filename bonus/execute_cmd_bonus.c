/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:41:19 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/21 04:41:19 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parse_cmd(t_pipex *pipex, char *cmd)
{
	pipex->cmd_args = ft_split(cmd, ' ');
	if (pipex->cmd_args == NULL)
		pipex_error("ft_split", 1);
}

char	**get_path_var(char **envp)
{
	char	*path_str;
	char	**arr;

	path_str = NULL;
	while (*envp)
	{
		if ((*envp)[0] == 'P' && (*envp)[1] == 'A'
			&& (*envp)[2] == 'T' && (*envp)[3] == 'H')
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
		pipex_error(NULL, 1);
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
			pipex_error(NULL, 1);
		tmp = ft_strjoin(str, cmd);
		free(str);
		if (tmp == NULL)
			pipex_error(NULL, 1);
		if (access(tmp, F_OK) == 0)
		{
			if (access(tmp, X_OK) != 0)
				pipex_error(tmp, 126);
			return (tmp);
		}
		free(tmp);
		path_var++;
	}
	pipex_cmd_not_found(cmd);
	return (NULL);
}

void	execute_command(t_pipex *pipex, char *cmd)
{
	char	**path_var;
	char	*cmd_path;

	parse_cmd(pipex, cmd);
	cmd = pipex->cmd_args[0];
	if (cmd == NULL)
		pipex_cmd_not_found("");
	path_var = get_path_var(pipex->envp);
	pipex->path_var = path_var;
	if (ft_strchr(cmd, '/'))
	{
		cmd_path = cmd;
		if (access(cmd_path, F_OK) != 0)
			pipex_error(cmd_path, 127);
		if (access(cmd_path, X_OK) != 0)
			pipex_error(cmd_path, 126);
	}
	else
		cmd_path = get_cmd_path(path_var, cmd);
	execve(cmd_path, pipex->cmd_args, pipex->envp);
	pipex_error(NULL, 1);
}

int	fork_and_execute(char *cmd, int fd_in, int fd_out)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		pipex_error("fork", 1);
	if (pid != 0)
		return (pid);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		pipex_error("dup2", 1);
	close(fd_out);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		pipex_error("dup2", 1);
	close(fd_in);
	execute_command(get_pipex(), cmd);
	return (-1);
}
