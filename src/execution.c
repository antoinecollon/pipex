/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:50:28 by acollon           #+#    #+#             */
/*   Updated: 2025/07/26 16:32:51 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envi)
{
	t_pipex	pip;

	if (ac != 5)
		error_exit("Wrong number of argument\n");
	parse_args(av, envi, &pip);
	return (0);
}
