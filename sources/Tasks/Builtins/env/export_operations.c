/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:26:16 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/21 12:44:33 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/builtins.h"
#include "../../../../include/executer.h"
#include "../../../../include/read.h"

static void	unset_and_export(char ***menvp, char *unset, char *export)
{
	*menvp = unset_from_menvp(unset, *menvp);
	*menvp = export_to_menvp(export, *menvp);
}

void	concat_export(char ***menvp, char **parsed)
{
	char	**old_value;
	char	*new_value;
	char	*tmp;

	old_value = parse_for_export((*menvp)[menvp_lookup(parsed[0], *menvp)]);
	tmp = ft_strjoin(parsed[0], "=");
	if (old_value[2] && parsed[2])
	{
		new_value = ft_strjoin(tmp, old_value[2]);
		free(tmp);
		tmp = ft_strjoin(new_value, parsed[2]);
		unset_and_export(menvp, parsed[0], tmp);
		free(new_value);
	}
	else if (!old_value[2] && parsed[2])
	{
		new_value = ft_strjoin(tmp, parsed[2]);
		unset_and_export(menvp, parsed[0], new_value);
		free(new_value);
	}
	else if ((old_value[0] && !old_value[1]) && parsed[1])
		unset_and_export(menvp, parsed[0], tmp);
	return (clear(old_value), free(tmp));
}

void	export_operation(char ***menvp, char *value, char **parsed, int op)
{
	char	*new_value;
	char	*tmp;

	if (op == 0)
	{
		*menvp = unset_from_menvp(parsed[0], *menvp);
		*menvp = export_to_menvp(value, *menvp);
	}
	if (op == 1)
	{
		tmp = ft_strjoin(parsed[0], "=");
		new_value = ft_strjoin(tmp, parsed[2]);
		*menvp = export_to_menvp(new_value, *menvp);
		free(new_value);
		free(tmp);
	}
	if (op == 2)
	{
		new_value = ft_strjoin(parsed[0], "=");
		*menvp = export_to_menvp(new_value, *menvp);
		free(new_value);
	}
}

void	update_shlvl(t_session *session)
{
	char	**parsed;
	char	*new_value;
	int		pos;
	int		level;

	pos = -1;
	level = 1;
	pos = menvp_lookup("SHLVL", session->menvp);
	if (pos > -1)
	{
		parsed = parse_for_export(session->menvp[pos]);
		level = ft_atoi(parsed[2]);
		level++;
		free(parsed[2]);
		parsed[2] = ft_itoa(level);
		new_value = ft_strjoin("SHLVL=", parsed[2]);
		m_export(&session->status, &session->menvp, new_value);
		free(new_value);
		clear(parsed);
	}
}
