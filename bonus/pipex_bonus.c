/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:40:46 by acollon           #+#    #+#             */
/*   Updated: 2025/08/07 16:00:47 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(t_pipex *pip)
{
	if (dup2(pip->pipefd[0], STDIN_FILENO) < 0)
		perror_exit(pip, "failed reading dup2");
	if (dup2(pip->pipefd[1], STDOUT_FILENO) < 0)
		perror_exit(pip, "failed writing dup2");
	execve(pip->cmd_path, pip->cmd, pip->envi);
	perror_exit(pip, "failed execve");
}

void	parent_process(t_pipex *pip)
{
		
}