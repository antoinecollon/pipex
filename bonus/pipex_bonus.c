/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:40:46 by acollon           #+#    #+#             */
/*   Updated: 2025/08/18 11:09:16 by acollon          ###   ########.fr       */
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
			perror_exit_child(pip, infile, outfile, "missing prev node");
		pip->pipefd[0] = pip->prev->pipefd[0];
	}
	if (pip->node_pos == NODE_LAST)
		pip->pipefd[1] = outfile;
	if (pip->pipefd[0] < 0)
		perror_exit_child(pip, infile, outfile, "bad stdin fd");
	if (pip->pipefd[1] < 0)
		perror_exit_child(pip, infile, outfile, "bad stdout fd");
	if (dup2(pip->pipefd[0], STDIN_FILENO) < 0)
		perror_exit_child(pip, infile, outfile, "failed reading dup2");
	if (dup2(pip->pipefd[1], STDOUT_FILENO) < 0)
		perror_exit_child(pip, infile, outfile, "failed writing dup2");
	close_child_fd(pip, infile, outfile);
	execve(pip->cmd_path, pip->cmd, pip->envi);
	perror_exit_child(pip, infile, outfile, "failed execve");
}

void	parent_process(t_pipex *pip, int infile, int outfile)
{
	t_pipex	*tmp;

	tmp = pip;
	while (tmp)
	{
		if (tmp->node_pos != NODE_LAST)
		{
			if (pipe(tmp->pipefd) == -1)
				perror_exit_parent(tmp, outfile, "pipe failed");
		}
		tmp->pid = fork();
		if (tmp->pid < 0)
			perror_exit_parent(tmp, outfile, "fork failed");
		if (tmp->pid == 0)
			child_process(tmp, infile, outfile);
		else
			close_parent_fd(tmp, infile);
		tmp = tmp->next;
	}
	close_last_fd(pip, outfile);
}

void	perror_exit_child(t_pipex *p, int in, int out, const char *context)
{
	perror(context);
	close_child_fd(p, in, out);
	free_all_node(p);
	_exit(1);
}

void	perror_exit_parent(t_pipex *pip, int outfile, const char *context)
{
	t_pipex	*tmp;

	perror(context);
	tmp = pip;
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	close_last_fd(tmp, outfile);
	free_all_node(pip);
	exit(1);
}

void	perror_exit(t_pipex *pip, const char *context)
{
	perror(context);
	if (pip->pipefd[0] != -1 && pip->pipefd[0] != STDIN_FILENO)
		close(pip->pipefd[0]);
	if (pip->pipefd[1] != -1 && pip->pipefd[1] != STDOUT_FILENO)
		close(pip->pipefd[1]);
	if (pip->prev && pip->prev->pipefd[0] != -1)
		close(pip->prev->pipefd[0]);
	perror_exit_parent(pip, -1, "");
}
