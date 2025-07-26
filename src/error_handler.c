/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:06:48 by acollon           #+#    #+#             */
/*   Updated: 2025/07/26 18:52:48 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	perror_exit(t_pipex *pip, const char *context)
{
	cleanup(pip);
	perror(context);
	exit(EXIT_FAILURE);
}

void	cleanup(t_pipex *pip)
{
	if (pip->cmd1)
		ft_free_split(pip->cmd1);
	if (pip->cmd2)
		ft_free_split(pip->cmd2);
	free(pip->cmd_path1);
	free(pip->cmd_path2);
	if (pip->infile > 0)
		close(pip->infile);
	if (pip->outfile > 0)
		close(pip->outfile);
}
