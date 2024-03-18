/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_variable_expansion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:31:45 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/15 15:19:16 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/executer.h"

static int	delta_size(int status, char *string, char **envp)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (string[0] == '?')
		return ((status > 99) + (status > 9) - 1);
	if (!ft_isalpha(string[0]) && string[0] != '_')
		return (0);
	while (ft_isalnum(string[i]) || string[i] == '_')
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

void	expand_variable(char **string, char **envp, char *new, int *j)
{
	int	k;

	k = 1;
	(*string)++;
	if (!ft_isalpha((*string)[0]) && (*string)[0] != '_')
	{
		new[(*j)++] = '$';
		return ;
	}
	(*string)++;
	while (ft_isalnum(**string) && k++)
		(*string)++;
	while (*envp)
	{
		if (ft_strncmp((*string - k), *envp, k) == 0 && (*envp)[k] == '=')
			break ;
		envp++;
	}
	if (*envp)
	{
		while ((*envp)[k + 1])
			new[(*j)++] = (*envp)[k++ + 1];
	}
}

static void	expand_status_variable(int status, char *new, int *j)
{
	if (status > 99)
		new[(*j)++] = status / 100 + 48;
	if (status > 9)
		new[(*j)++] = status % 100 / 10 + 48;
	new[(*j)++] = status % 10 + 48;
}

static char	*transfer_string(t_session *session,
		char *string, char *new, char flag)
{
	int		j;
	int		qt;
	int		qts;
	char	*original;

	j = 0;
	qt = 0;
	qts = 0;
	original = string;
	while (*string)
	{
		if (*string == '\'' && !(qts % 2))
			qt++;
		if (*string == '\"')
			qts++;
		if (*string == '$' && !(qt % 2) && *(string + 1) != '?')
			expand_variable(&(string), session->menvp, new, &j);
		else if (*string == '$' && !(qt % 2) && string++ && string++)
			expand_status_variable((session->status & 0xff00) >> 8, new, &j);
		else
			new[j++] = *(string++);
	}
	if (flag)
		free(original);
	return (new);
}

void	ambient_variable_expansion(t_session *session, char **string, char flag)
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
	while (*string && (*string)[++i])
	{
		if ((*string)[i] == '\'' && !(qts % 2))
			qt++;
		if ((*string)[i] == '\"')
			qts++;
		if ((*string)[i] == '$' && !(qt % 2))
			j += delta_size((session->status & 0xff00) >> 8,
					&(*string)[i + 1], session->menvp);
	}
	new = malloc(i + j + 1);
	if (!new)
		return ;
	new[i + j] = 0;
	*string = transfer_string(session, *string, new, flag);
}
