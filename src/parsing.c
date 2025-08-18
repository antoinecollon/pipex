/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:41:37 by acollon           #+#    #+#             */
/*   Updated: 2025/08/14 15:06:01 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	**get_path(char **envi)
{
	int	i;

	i = 0;
	while (envi && envi[i])
	{
		if (ft_strncmp(envi[i], "PATH=", 5) == 0)
			return (ft_split(envi[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

static char	*get_cmd_path(char *cmd, char **envi)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	if (!cmd || !*cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = get_path(envi);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free (tmp);
		if (access(path, X_OK) == 0)
			return (ft_free_split(paths), path);
		free(path);
		i++;
	}
	return (ft_free_split(paths), NULL);
}

void	parse_args(char **av, char **envi, t_pipex *pip)
{
	pip->infile = open(av[1], O_RDONLY);
	if (pip->infile < 0)
		perror_exit(pip, av[1]);
	pip->outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pip->outfile < 0)
		perror_exit(pip, av[4]);
	pip->cmd1 = ft_split(av[2], ' ');
	pip->cmd2 = ft_split(av[3], ' ');
	if (!pip->cmd1 || !pip->cmd2)
		perror_exit(pip, "Split failed");
	if (!pip->cmd1[0] ||!pip->cmd2[0])
		perror_exit(pip, "Empty command");
	pip->cmd_path1 = get_cmd_path(pip->cmd1[0], envi);
	pip->cmd_path2 = get_cmd_path(pip->cmd2[0], envi);
	if (!pip->cmd_path1 || !pip->cmd_path2)
		perror_exit(pip, "Command not found");
	pip->envi = envi;
}
