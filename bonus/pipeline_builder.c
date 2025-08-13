/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 10:40:59 by acollon           #+#    #+#             */
/*   Updated: 2025/08/10 11:19:48 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	init_node_info(t_pipex *pip, int pos, char **envi)
{
	pip->node_pos = pos;
	pip->pipefd[0] = -1;
	pip->pipefd[1] = -1;
	pip->pid = -1;
	pip->envi = envi;
	pip->next = NULL;
	pip->prev = NULL;
}

static t_pipex	*create_node(char *cmd, char **envi, int pos)
{
	t_pipex	*pip;

	pip = (t_pipex *)malloc(sizeof(t_pipex));
	if (!pip)
		return (NULL);
	init_node_info(pip, pos, envi);
	pip->cmd = ft_split(cmd, ' ');
	if (!pip->cmd || !pip->cmd[0])
	{
		if (pip->cmd)
			ft_free_split(pip->cmd);
		return (free(pip), NULL);
	}
	pip->cmd_path = get_cmd_path(pip->cmd[0], envi);
	if (!pip->cmd_path)
	{
		ft_free_split(pip->cmd);
		return (free(pip), NULL);
	}
	return (pip);
}

static void	double_link(t_pipex **head, t_pipex *pip)
{
	t_pipex	*tmp;

	if (!pip)
		return ;
	pip->next = NULL;
	if (!*head)
	{
		pip->prev = NULL;
		*head = pip;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = pip;
	pip->prev = tmp;
}

static int	node_pos(int i, int ac)
{
	if (i == 2)
		return (NODE_FIRST);
	if (i == ac - 2)
		return (NODE_LAST);
	return (NODE_MIDDLE);
}

t_pipex	*build_pipeline(int ac, char **av, char **envi)
{
	t_pipex	*pip;
	t_pipex	*head;
	int		i;
	int		pos;

	head = NULL;
	if (ac < 5)
		return (NULL);
	i = 2;
	while (i <= ac - 2)
	{
		pos = node_pos(i, ac);
		pip = create_node(av[i], envi, pos);
		if (!pip)
		{
			free_pipeline(&head);
			return (NULL);
		}
		double_link(&head, pip);
		i++;
	}
	return (head);
}
