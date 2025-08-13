/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:40:46 by acollon           #+#    #+#             */
/*   Updated: 2025/08/10 11:59:44 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(t_pipex *pip, int infile, int outfile)
{
	if (pip->node_pos == NODE_FIRST)
		pip->pipefd[0] = infile;
	else
	{
		if (!pip->prev)
			perror_exit(pip, "missing prev node");
		pip->pipefd[0] = pip->prev->pipefd[0];
	}
	if (pip->node_pos == NODE_LAST)
		pip->pipefd[1] = outfile;
	if (dup2(pip->pipefd[0], STDIN_FILENO) < 0)
		perror_exit(pip, "failed reading dup2");
	if (dup2(pip->pipefd[1], STDOUT_FILENO) < 0)
		perror_exit(pip, "failed writing dup2");
	close_child_fd(pip, infile, outfile);
	execve(pip->cmd_path, pip->cmd, pip->envi);
	perror_exit(pip, "failed execve");
}

void	parent_process(t_pipex *pip, int infile, int outfile)
{
	t_pipex	*tmp;

	tmp = pip;
	while (tmp)
	{
		if (tmp->node_pos != NODE_LAST)
			pipe(tmp->pipefd);
		if (!tmp->pipefd)
			return ;
		else
		{
			tmp->pipefd[0] = -1;
			tmp->pipefd[1] = -1;
		}
		tmp->pid = fork();
		if (tmp->pid < 0)
			perror_exit(tmp, "fork failed");
		if (tmp->pid == 0)
			child_process(tmp, infile, outfile);
		else
			close_parent_fd(tmp, infile);
		tmp = tmp->next;
	}
	close_last_fd(pip, outfile);
}

void	perror_exit_child(t_pipex *pip, int infile, int outfile, char *context)
{
	perror(context);
	close_child_fd(pip, infile, outfile);
	_exit
}