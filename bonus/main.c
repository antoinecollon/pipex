/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:07:06 by acollon           #+#    #+#             */
/*   Updated: 2025/08/15 17:06:44 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_infile(int ac, char **av)
{
	int	fd;

	if (is_here_doc(ac, av))
		return (here_doc_read(av[2]));
	fd = open(av[1], O_RDONLY);
	return (fd);
}

static int	open_files(int ac, char **av, int *infile)
{
	if (ac < 5)
	{
		ft_putendl_fd("Usage : ./pipex infile cmd1 ... outfile", 2);
		return (1);
	}
	*infile = open_infile(ac, av);
	if (*infile < 0)
	{
		perror("open infile");
		return (1);
	}
	return (0);
}

int	open_outfile(int ac, char **av)
{
	int	fd;

	if (is_here_doc(ac, av))
		fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	main(int ac, char **av, char **envi)
{
	t_pipex	*pip;
	int		infile;
	int		outfile;

	ft_printf("%s\n", "Starting pipex");
	if (open_files(ac, av, &infile))
		return (1);
	pip = build_pipeline(ac, av, envi);
	if (!pip)
	{
		close(infile);
		ft_putendl_fd("pipex failed to build pipeline", 2);
		return (1);
	}
	outfile = open_outfile(ac, av);
	if (outfile < 0)
	{
		perror("open outfile");
		close(infile);
		return (1);
	}
	parent_process(pip, infile, outfile);
	free_all_node(pip);
	return (0);
}
