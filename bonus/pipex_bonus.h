/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:41:10 by acollon           #+#    #+#             */
/*   Updated: 2025/08/10 11:41:16 by acollon          ###   ########.fr       */
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

typedef enum e_pos
{
	NODE_FIRST = -1,
	NODE_MIDDLE = 0,
	NODE_LAST = 1	
}	t_pos;

typedef struct s_pipex
{
	t_pos			node_pos;
	int				pipefd[2];
	pid_t			pid;
	char			**cmd;
	char			*cmd_path;
	char			**envi;
	struct s_pipex	*next;
	struct s_pipex	*prev;
}	t_pipex;

/* handle_close.c  */
void	close_child_fd(t_pipex *pip, int infile, int outfile);
void	close_parent_fd(t_pipex *pip, int infile);
void	close_last_fd(t_pipex *pip, int outfile);
void	free_pipeline(t_pipex **pip);

/* pipeline_builder.c */
t_pipex	*build_pipeline(int ac, char **av, char **envi);

/* parsing_bonus.c */
char	**get_path(char **envi);
char	*get_cmd_path(char *cmd, char **envi);

#endif