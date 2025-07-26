/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:50:28 by acollon           #+#    #+#             */
/*   Updated: 2025/07/26 18:25:25 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child1(t_pipex *pip)
{
	if (dup2(pip->infile, STDIN_FILENO) < 0)
		perror_exit("dup2 infile\n");
	if (dup2(pip->pipefd[1], STDOUT_FILENO) < 0)
		perror_exit("dup2 pipe write\n");
	close (pip->pipefd[0]);
	close(pip->pipefd[1]);
	close(pip->infile);
	close(pip->outfile);
	execve(pip->cmd_path1, pip->cmd1, pip->envi);
	perror_exit("execve cmd1\n");
}

void	child2(t_pipex *pip)
{
	if (dup2(pip->pipefd[0], STDIN_FILENO) < 0)
		perror_exit("dup2 pipe read");
	if (dup2(pip->outfile, STDOUT_FILENO) < 0)
		perror_exit("dup2 outfile");
	close(pip->pipefd[1]);
	close(pip->pipefd[0]);
	close(pip->infile);
	close(pip->outfile);
	execve(pip->cmd_path2, pip->cmd2, pip->envi);
	perror_exit("execve cmd2");
}

void	execute(t_pipex *pip)
{
	if (pipe(pip->pipefd) < 0)
		perror_exit("pipe");
	pip->pid1 = fork();
	if (pip->pid1 < 0)
		perror_exit("fork");
	if (pip->pid1 == 0)
		child1(pip);
	pip->pid2 = fork();
	if (pip->pid2 < 0)
		perror_exit("fork");
	if (pip->pid2 == 0)
		child2(pip);
	close (pip->pipefd[0]);
	close (pip->pipefd[1]);
	waitpid(pip->pid1, NULL, 0);
	waitpid(pip->pid2, NULL, 0);
}

int	main(int ac, char **av, char **envi)
{
	t_pipex	pip;

	if (ac != 5)
		perror_exit("Wrong number of argument");
	parse_args(av, envi, &pip);
	execute(&pip);
	cleanup(&pip);
	return (0);
}
