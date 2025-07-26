/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:41:54 by acollon           #+#    #+#             */
/*   Updated: 2025/07/26 18:24:12 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**cmd1;
	char	**cmd2;
	char	*cmd_path1;
	char	*cmd_path2;
	char	**envi;
}	t_pipex;

/* error_handler.c*/
void	perror_exit(const char *context);
void	cleanup(t_pipex *pip);

/* parsing.c */
void	parse_args(char **av, char **envp, t_pipex *pip);

/* execution.c */
void	execute(t_pipex *pip);
void	child1(t_pipex *pip);
void	child2(t_pipex *pip);

#endif