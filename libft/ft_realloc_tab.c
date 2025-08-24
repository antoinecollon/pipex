/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:57:18 by acollon           #+#    #+#             */
/*   Updated: 2025/08/24 13:21:38 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_realloc_tab(char ***tab, char *new_str, int *count)
{
	char	**old_tab;
	char	**new_tab;
	int		i;

	old_tab = *tab;
	new_tab = (char **)malloc(sizeof(char *) * (*count + 2));
	if (!new_tab)
		return (0);
	i = 0;
	while (i < *count)
	{
		new_tab[i] = old_tab[i];
		i++;
	}
	new_tab[i] = new_str;
	new_tab[i + 1] = NULL;
	*tab = new_tab;
	if (old_tab)
		free(old_tab);
	(*count)++;
	return (1);
}
