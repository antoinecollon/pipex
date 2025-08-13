/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:41:19 by acollon           #+#    #+#             */
/*   Updated: 2025/08/10 11:35:54 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_child_fd(t_pipex *pip, int infile, int outfile)
{
	if (pip->pipefd[0] != -1 && pip->pipefd[0] != STDIN_FILENO)
		close(pip->pipefd[0]);
	if (pip->pipefd[1] != -1 && pip->pipefd[1] != STDOUT_FILENO)
		close(pip->pipefd[1]);
	if (infile != -1 && infile != STDIN_FILENO)
		close(infile);
	if (outfile != -1 && outfile != STDOUT_FILENO)
		close(outfile);
}

void	close_parent_fd(t_pipex *pip, int infile)
{
	if (pip->node_pos == NODE_FIRST && infile >= 0)
		close(infile);
	if (pip->prev && pip->prev->pipefd[0] >= 0)
		close(pip->prev->pipefd[0]);
	if (pip->node_pos != NODE_LAST && pip->pipefd[1] >= 0)
		close(pip->pipefd[1]);
}

void	close_last_fd(t_pipex *pip, int outfile)
{
	t_pipex	*tmp;

	tmp = pip;
	if (outfile >= 0)
		close(outfile);
	while (tmp)
	{
		if (tmp->pid > 0)
			waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
}

void	free_pipeline(t_pipex **pip)
{
	t_pipex	*tmp;

	while (*pip)
	{
		tmp = (*pip)->next;
		if ((*pip)->cmd)
			ft_free_split((*pip)->cmd);
		free((*pip)->cmd_path);
		free(*pip);
		*pip = tmp;
	}
}

