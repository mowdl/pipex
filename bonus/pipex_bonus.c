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

#include "pipex_bonus.h"
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
	if (dup2(pipex->pipe_fd[0][1], STDOUT_FILENO) == -1)
		pipex_error("dup2", 1);
	close(pipex->pipe_fd[0][1]);
	close(pipex->pipe_fd[0][0]);
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
	if (dup2(pipex->pipe_fd[0][0], STDIN_FILENO) == -1)
		pipex_error("dup2", 1);
	close(pipex->pipe_fd[0][1]);
	close(pipex->pipe_fd[0][0]);
	execute_command(pipex, pipex->av[pipex->ac - 2]);
	return (-1);
}

int	fork_and_execute(char *cmd, int fd_in, int fd_out)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		pipex_error("fork", 1);
	if (pid !=0)
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

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipex;
	int		wstatus;
	int		i;

	if (ac < 4)
		pipex_error(NULL, 1);
	pipex = get_pipex();
	pipex->av = av;
	pipex->ac = ac;
	pipex->envp = envp;
	if (pipe(pipex->pipe_fd[0]) == -1)
		pipex_error("pipe", 1);
	pipex->pids = malloc(sizeof(int) * (ac - 3));
	if (pipex->pids == NULL)
		pipex_error(NULL, 1);
	pipex->pids[0] = first_cmd(pipex);
	close(pipex->pipe_fd[0][1]);
	i = 3;
	while (i < ac - 2)
	{
		if (pipe(pipex->pipe_fd[1]) == -1)
			pipex_error("pipe", 1);
		pipex->pids[i - 2] = fork_and_execute(av[i], pipex->pipe_fd[0][0], pipex->pipe_fd[1][1]);
		close(pipex->pipe_fd[0][0]);
		close(pipex->pipe_fd[1][1]);
		pipex->pipe_fd[0][0] = pipex->pipe_fd[1][0];
		i++;
	}
	pipex->pids[ac - 3 - 1] = last_cmd(pipex);
	close(pipex->pipe_fd[0][0]);
	i = 0;
	wstatus = 0;
	while (i < ac - 3)
		waitpid(pipex->pids[i++], &wstatus, 0);
	free(pipex->pids);
	exit(((wstatus) & 0xff00) >> 8);
}
