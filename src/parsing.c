/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:41:37 by acollon           #+#    #+#             */
/*   Updated: 2025/07/22 10:33:49 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	paths = NULL;
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free (tmp);
		if (access(path, X_OK) == 0)
			return (free_split(paths), path);
		free(path);
		i++;
	}
	return (free_split(paths), NULL);
}

void	parse_args(char **av, char **envp, t_pipex *pip)
{
	pip->infile = open(av[1], O_RDONLY);
	if (pip->infile < 0)
		perror_exit(av[1]);
	pip->outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pip->outfile < 0)
		perror_exit(av[4]);
	pip->cmd1 = ft_split(av[2], ' ');
	pip->cmd2 = ft_split(av[3], ' ');
	if (!pip->cmd1 || !pip->cmd2)
		error_exit("Split failed\n");
	if (!pip->cmd1[0] ||!pip->cmd2[0])
		error_exit("Empty command\n");
	pip->cmd_path1 = get_cmd_path(pip->cmd1[0], envp);
	pip->cmd_path2 = get_cmd_path(pip->cmd2[0], envp);
	if (!pip->cmd_path1 || !pip->cmd_path2)
		error_exit("Command not found\n");
	pip->envp = envp;		
}
