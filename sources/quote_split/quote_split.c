/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:55:43 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/05 16:25:32 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/quote_split.h"

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

static int	count_words(char const *s, char c)
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
		if ((i == 0 || s[i - 1] == c) && s[i] != c && !(qt % 2) && !(qts % 2))
			count++;
		if (s[i] == '\'')
			qt++;
		if (s[i] == '\"')
			qts++;
		i++;
	}
	return (count);
}

static char	**initialize_table(char const *s, char c)
{
	int		words;
	char	**table;

	words = count_words(s, c);
	table = malloc(words * 8 + 8);
	if (!table)
		return (0);
	table[words] = 0;
	return (table);
}

static void	initialize_vars(int *i, int *j, int *k, t_qt *qt)
{
	*i = -1;
	*j = -1;
	*k = 0;
	qt->qt = 0;
	qt->qts = 0;
}

char	**quote_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	t_qt	qt;
	char	**table;

	initialize_vars(&i, &j, &k, &qt);
	table = initialize_table(s, c);
	while (table && s[++i])
	{
		if ((!i || s[i - 1] == c) && s[i] != c && !(qt.qt % 2) && !(qt.qts % 2))
			j = i;
		if (s[i] == '\'')
			qt.qt++;
		if (s[i] == '\"')
			qt.qts++;
		if (((s[i + 1] == c && !(qt.qt % 2) && !(qt.qts % 2))
				|| s[i + 1] == 0) && j != -1)
		{
			table[k] = ft_strndup(&s[j], i - j + 1, &table, k);
			k++;
			j = -1;
		}
	}
	return (table);
}
