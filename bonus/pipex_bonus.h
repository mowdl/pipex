/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 05:47:30 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/20 05:29:58 by mel-meka         ###   ########.fr       */
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
	int		pipe_fd[2][2];
	char	*cmd;
	char	**cmd_args;
	char	**path_var;
	int		fd;
	int		*pids;
}			t_pipex;

t_pipex	*get_pipex(void);

void	execute_command(t_pipex *pipex, char *cmd);
void	pipex_error(char *str, int v);
void	pipex_cmd_not_found(char *cmd);

#endif
