/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 05:47:09 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/20 02:07:35 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "mm_vector.h"

t_pipex	*get_pipex(void)
{
	static t_pipex	pipex;

	return (&pipex);
}

void	child_proc(t_pipex  *pipex)
{
	pipex->fd = open(pipex->av[1], O_RDONLY);
	if (pipex->fd == -1)
		pipex_error(pipex->av[1]);
	if (dup2(pipex->fd, STDIN_FILENO) == -1)
		pipex_error("dup2");
	close(pipex->fd);
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		pipex_error("dup2");
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
	execute_command(pipex, pipex->av[2]);
}

void	parent_proc(t_pipex  *pipex)
{
	pipex->fd = open(pipex->av[4], O_CREAT | O_WRONLY, S_IRUSR + S_IWUSR + S_IRGRP + S_IROTH);
	if (pipex->fd == -1)
		pipex_error(pipex->av[4]);
	if (dup2(pipex->fd, STDOUT_FILENO) == -1)
		pipex_error("dup2");
	close(pipex->fd);
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
		pipex_error("dup2");
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
	execute_command(pipex, pipex->av[3]);
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
	else
		parent_proc(pipex);
}
