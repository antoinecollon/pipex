/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 09:46:10 by acollon           #+#    #+#             */
/*   Updated: 2025/08/15 17:19:36 by acollon          ###   ########.fr       */
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

int	is_here_doc(int ac, char **av)
{
	if (ac >= 6 && ft_strncmp(av[1], "here_doc", 9) == 0)
		return (1);
	return (0);
}

int	here_doc_read(const char *limit)
{
	int		fd[2];
	char	*line;
	size_t	len;

	if (pipe(fd) == -1)
		return (-1);
	len = ft_strlen(limit);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if ((ft_strlen(line) == len + 1)
			&& ft_strncmp(line, limit, len) == 0
			&& line[len] == '\n')
		{
			free(line);
			break ;
		}
		write (fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

// char	**split_with_quotes(const char *str)
// {
// 	int		i;
// 	int		count;
// 	char	**split;
// 	char	*word;

// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	count = 0;
// 	split = NULL;
// 	while (str[i])
// 	{
// 		skip_spaces(str, &i);
// 		if (!str[i])
// 			break ;
// 		word = get_word(str, &i);
// 		if (!word)
// 			return (ft_free_split(split), NULL);
// 		split = ft_realloc_tab(split, word, &count);
// 		if (!split)
// 			return (NULL);
// 	}
// 	return (split);
// }
char	**split_with_quotes(const char *str)
{
	int		i;
	int		count;
	char	**split;
	char	*word;

	if (!str)
		return (NULL);
	i = 0;
	count = 0;
	split = NULL;
	while (str[i])
	{
		skip_spaces(str, &i);
		if (!str[i])
			break ;
		word = get_word(str, &i);
		if (!word)
			return (ft_free_split(split), NULL);
		if (!ft_realloc_tab(&split, word, &count))
			return (ft_free_split(split), free(word), NULL);
	}
	return (split);
}
