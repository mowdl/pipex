/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 05:47:09 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/21 00:27:10 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "mm_vector.h"

t_pipex	*get_pipex(void)
{
	static t_pipex	pipex;

	return (&pipex);
}

void	first_cmd(t_pipex *pipex)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
		pipex_error("fork", 1);
	if (pipex->pid != 0)
		return ;
	pipex->fd = open(pipex->av[1], O_RDONLY);
	if (pipex->fd == -1)
		pipex_error(pipex->av[1], 1);
	if (dup2(pipex->fd, STDIN_FILENO) == -1)
		pipex_error("dup2", 1);
	close(pipex->fd);
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		pipex_error("dup2", 1);
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
	execute_command(pipex, pipex->av[2]);
}

void	second_cmd(t_pipex *pipex)
{
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
		pipex_error("fork", 1);
	if (pipex->pid2 != 0)
		return ;
	pipex->fd = open(pipex->av[4], O_CREAT | O_WRONLY,
			S_IRUSR + S_IWUSR + S_IRGRP + S_IROTH);
	if (pipex->fd == -1)
		pipex_error(pipex->av[4], 1);
	if (dup2(pipex->fd, STDOUT_FILENO) == -1)
		pipex_error("dup2", 1);
	close(pipex->fd);
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
		pipex_error("dup2", 1);
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
	execute_command(pipex, pipex->av[3]);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipex;
	int		wstatus;

	pipex = get_pipex();
	pipex->av = av;
	pipex->ac = ac;
	pipex->envp = envp;
	if (pipe(pipex->pipe_fd) == -1)
		pipex_error("pipe", 1);
	first_cmd(pipex);
	second_cmd(pipex);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(pipex->pid, NULL, 0);
	waitpid(pipex->pid2, &wstatus, 0);
	exit(((wstatus) & 0xff00) >> 8);
}
