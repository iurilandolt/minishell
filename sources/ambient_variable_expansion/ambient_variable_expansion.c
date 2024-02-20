/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_variable_expansion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:31:45 by rcastelo          #+#    #+#             */
/*   Updated: 2024/02/09 16:17:08 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n);

static int	ft_isalnum(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	delta_size(char *string, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ft_isalnum(string[i]))
		i++;
	if (i == 0)
		return (0);
	while (*envp)
	{
		if (ft_strncmp(string, *envp, i) == 0 && (*envp)[i] == '=')
			break ;
		envp++;
	}
	if (*envp == 0)
		return (-i - 1);
	while ((*envp)[i + 1 + j])
		j++;
	return (j - i - 1);
}

void	expand_variable(char *string, char **envp, char *new, int *j)
{
	int	k;

	k = 0;
	while (ft_isalnum(string[k]))
		k++;
	if (k == 0)
	{
		new[(*j)++] = '$';
		return ;
	}
	while (*envp)
	{
		if (ft_strncmp(string, *envp, k) == 0 && (*envp)[k] == '=')
			break ;
		envp++;
	}
	if (*envp)
	{
		while ((*envp)[k + 1])
			new[(*j)++] = (*envp)[k++ + 1];
	}
}

static char	*transfer_string(char *string, char **envp, char *new)
{
	int	i;
	int	j;
	int	qt;
	int	qts;

	i = -1;
	j = 0;
	qt = 0;
	qts = 0;
	while (string[++i])
	{
		if (string[i] == '\'' && !(qts % 2))
			qt++;
		if (string[i] == '\"')
			qts++;
		if (string[i] == '$' && (i == 0 || string[i - 1] != '\\') && !(qt % 2))
		{
			expand_variable(&string[i + 1], envp, new, &j);
			while (ft_isalnum(string[i + 1]))
				i++;
		}
		else
			new[j++] = string[i];
	}
	return (new);
}

int	ambient_variable_expansion(char **string, char **envp)
{
	int		i;
	int		j;
	int		qt;
	int		qts;
	char	*new;

	i = -1;
	j = 0;
	qt = 0;
	qts = 0;
	while ((*string)[++i])
	{
		if ((*string)[i] == '\'' && !(qts % 2))
			qt++;
		if ((*string)[i] == '\"')
			qts++;
		if ((*string)[i] == '$' && (i == 0 || (*string)[i - 1] != '\\') && !(qt % 2))
			j += delta_size(&(*string)[i + 1], envp);
	}
	new = malloc(i + j + 1);
	if (!new)
		return (1);
	new[i + j] = 0;
	*string = transfer_string(*string, envp, new);
	return (0);
}
