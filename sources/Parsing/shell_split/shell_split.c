/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:27:40 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/21 12:36:33 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"

static char	*ft_strndup(const char *str, int n, char ***table, int k)
{
	int		i;
	char	*new;

	new = malloc(n + 1);
	if (!new)
	{
		i = 0;
		while (i < k)
			free((*table)[i++]);
		free(*table);
		*table = 0;
		return (0);
	}
	new[n] = 0;
	while (--n >= 0)
		new[n] = str[n];
	return (new);
}

static int	count_words(char const *s)
{
	int	i;
	int	qt;
	int	qts;
	int	count;

	i = 0;
	qt = 0;
	qts = 0;
	count = 0;
	while (s[i])
	{
		if ((i == 0 || s[i - 1] == ' ' || s[i - 1] == '\t')
			&& s[i] != ' ' && s[i] != '\t' && !(qt % 2) && !(qts % 2))
			count++;
		if (s[i] == '\'')
			qt++;
		if (s[i] == '\"')
			qts++;
		i++;
	}
	return (count);
}

static char	**initialize_table(char const *s)
{
	int		words;
	char	**table;

	words = count_words(s);
	table = malloc(words * 8 + 8);
	if (!table)
		return (0);
	table[words] = 0;
	return (table);
}

static void	initialize_vars(int *i, int *j, int *k)
{
	*i = -1;
	*j = -1;
	*k = 0;
}

char	**shell_split(char const *s, int qt, int qts)
{
	int		i;
	int		j;
	int		k;
	char	**table;

	initialize_vars(&i, &j, &k);
	table = initialize_table(s);
	while (table && s[++i])
	{
		if ((!i || s[i - 1] == ' ' || s[i - 1] == '\t') && s[i] != ' ' 
			&& s[i] != '\t' && !(qt % 2) && !(qts % 2))
			j = i;
		if (s[i] == '\'')
			qt++;
		if (s[i] == '\"')
			qts++;
		if ((((s[i + 1] == ' ' | s[i + 1] == '\t') && !(qt % 2) && !(qts % 2))
				|| s[i + 1] == 0) && j != -1)
		{
			table[k] = ft_strndup(&s[j], i - j + 1, &table, k);
			k++;
			j = -1;
		}
	}
	return (table);
}