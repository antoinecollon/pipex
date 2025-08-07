/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:41:10 by acollon           #+#    #+#             */
/*   Updated: 2025/08/07 15:44:55 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	int				node_pos;
	int				pipefd[2];
	pid_t			pid;
	char			**cmd;
	char			*cmd_path;
	char			**envi;
	struct s_pipex	*next;
}	t_pipex;

/* error_handler.c */
void	perror_exit(t_pipex *pip, const char *context);
#endif