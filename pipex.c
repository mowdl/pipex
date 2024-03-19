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

t_pipex	*get_pipex(void)
{
	static t_pipex	pipex;

	return (&pipex);
}

void	pipex_error(char *str)
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
	exit(1);
}

char	**get_path_var(char **envp)
{
	char	*path_str;
	char	**arr;

	path_str == NULL;
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

char	*get_cmd_path(char **path_var)
{
	return (path_var[0]);
}

void	execute_command(t_pipex *pipex, char *cmd)
{
	char	**path_var;
	char	*cmd_path;

	path_var = get_path_var(pipex->envp);
	cmd_path = get_cmd_path(path_var);

	ft_printf("%p, %p\n", path, cmd);
}

void	child_proc(t_pipex  *pipex)
{
	pipex->fd = open(pipex->av[1], O_RDONLY);
	if (pipex->fd == -1)
		pipex_error(pipex->av[1]);
	if (dup2(pipex->fd, STDIN_FILENO) == -1)
		pipex_error("dup2");
	close(pipex->fd);
	//if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
	//	pipex_error("dup2");
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
	execute_command(pipex, pipex->av[2]);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipex;

	pipex = get_pipex();
	pipex->av = av;
	pipex->ac = ac;
	pipex->envp = envp;
	if (pipe(pipex->pipe_fd) == -1)
		pipex_error("pipe");

	pipex->pid = fork();
	if (pipex->pid == -1)
		pipex_error("fork");

	if (pipex->pid == 0)
		child_proc(pipex);
}
