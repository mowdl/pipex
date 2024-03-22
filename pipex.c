/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:40:57 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/21 04:40:57 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "mm_vector.h"

t_pipex	*get_pipex(void)
{
	static t_pipex	pipex;

	return (&pipex);
}

int	first_cmd(t_pipex *pipex)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		pipex_error("fork", 1);
	if (pid != 0)
		return (pid);
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
	return (-1);
}

int	last_cmd(t_pipex *pipex)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		pipex_error("fork", 1);
	if (pid != 0)
		return (pid);
	pipex->fd = open(pipex->av[pipex->ac - 1], O_CREAT | O_WRONLY,
			S_IRUSR + S_IWUSR + S_IRGRP + S_IROTH);
	if (pipex->fd == -1)
		pipex_error(pipex->av[pipex->ac -1], 1);
	if (dup2(pipex->fd, STDOUT_FILENO) == -1)
		pipex_error("dup2", 1);
	close(pipex->fd);
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
		pipex_error("dup2", 1);
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
	execute_command(pipex, pipex->av[pipex->ac - 2]);
	return (-1);
}

void	exec_cmds_from_argv(t_pipex *pipex)
{
	if (pipe(pipex->pipe_fd) == -1)
		pipex_error("pipe", 1);
	pipex->pids[0] = first_cmd(pipex);
	close(pipex->pipe_fd[1]);
	pipex->pids[1] = last_cmd(pipex);
	close(pipex->pipe_fd[0]);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipex;
	int		wstatus;
	int		i;

	if (ac != 5)
		exit(1);
	pipex = get_pipex();
	pipex->av = av;
	pipex->ac = ac;
	pipex->envp = envp;
	exec_cmds_from_argv(pipex);
	i = 0;
	wstatus = 0;
	while (i < ac - 3)
		waitpid(pipex->pids[i++], &wstatus, 0);
	exit(((wstatus) & 0xff00) >> 8);
}
