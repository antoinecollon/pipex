/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:50:28 by acollon           #+#    #+#             */
/*   Updated: 2025/07/22 10:00:35 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av)
{
	t_pipex	pip;

	if (ac != 5)
		error_exit("Wrong number of argument\n");
	parse_args(ac, av, envp, &pip);

	return (0);
}
