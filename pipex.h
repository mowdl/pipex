/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 05:47:30 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/20 01:19:03 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"


typedef struct s_pipex
{
	char	**av;
	char	**envp;
	int		ac;
	int		pipe_fd[2];
	char	*cmd;
	char	**cmd_args;
	int		fd;
	int		pid;
}			t_pipex;

t_pipex	*get_pipex(void);

void	execute_command(t_pipex *pipex, char *cmd);
void	pipex_error(char *str);

#endif
