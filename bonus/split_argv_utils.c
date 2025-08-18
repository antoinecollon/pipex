/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_argv_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:10:41 by acollon           #+#    #+#             */
/*   Updated: 2025/08/16 09:31:40 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	skip_spaces(const char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
}

size_t	word_len(const char *str, int start, int end)
{
	size_t	len;
	int		i;

	i = start;
	len = 0;
	while (i < end)
	{
		if (str[i] == '\\' && i + 1 < end
			&& (str[i + 1] == '"' || str[i + 1] == '\''))
		{
			i += 2;
			continue ;
		}
		if (str[i] != '"' && str[i] != '\'')
			len++;
		i++;
	}
	return (len);
}

int	find_word_end(const char *str, int start, char *quote_state)
{
	char	quote;

	quote = '\0';
	while (str[start])
	{
		if (str[start] == '\\' && str[start + 1]
			&& (str[start + 1] == '"' || str[start + 1] == '\''))
		{
			start += 2;
			continue ;
		}
		if (!quote && (str[start] == '\'' || str[start] == '"'))
			quote = str[start++];
		else if (quote && str[start] == quote)
		{
			quote = '\0';
			start++;
		}
		else if (!quote && (str[start] == ' ' || str[start] == '\t'))
			break ;
		else
			start++;
	}
	*quote_state = quote;
	return (start);
}

void	copy_word(char *cpy, const char *str, int start, int end)
{
	int	j;
	int	i;

	j = start;
	i = 0;
	while (j < end)
	{
		if (str[j] == '\\' && j + 1 < end
			&& (str[j + 1] == '"' || str[j + 1] == '\''))
		{
			j += 2;
			continue ;
		}
		if (str[j] != '"' && str[j] != '\'')
			cpy[i++] = str[j];
		j++;
	}
	cpy[i] = '\0';
}

char	*get_word(const char *str, int *i)
{
	int		len;
	char	quote_state;
	char	*word;
	int		end;
	int		start;

	start = *i;
	end = find_word_end(str, start, &quote_state);
	len = word_len(str, start, end);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	copy_word(word, str, start, end);
	*i = end;
	return (word);
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
// 		if (!ft_realloc_tab(&split, word, &count))
// 			return (ft_free_split(split), free(word), NULL);
// 	}
// 	return (split);
// }

// int	main(int ac, char **av)
// {
// 	if (ac < 2)
// 		return (1);
// 	char	**tests = av;
// 	int		t;

// 	for (t = 0; tests[t]; t++)
// 	{
// 		printf("Test %d : \"%s\"\n", t + 1, tests[t]);
// 		char **split = split_with_quotes(tests[t]);
// 		if (!split)
// 		{
// 			printf("Erreur : allocation échouée\n");
// 			continue;
// 		}
// 		for (int i = 0; split[i]; i++)
// 			printf("  [%d] \"%s\"\n", i, split[i]);
// 		ft_free_split(split);
// 		printf("\n");
// 	}
// 	return (0);
// }