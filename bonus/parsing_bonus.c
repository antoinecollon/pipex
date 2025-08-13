/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 09:46:10 by acollon           #+#    #+#             */
/*   Updated: 2025/08/10 11:40:41 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**get_path(char **envi)
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

char	*get_cmd_path(char *cmd, char **envi)
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
		free(tmp);
		if (access(path, X_OK) == 0)
			return (ft_free_split(paths), path);
		free(path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}
