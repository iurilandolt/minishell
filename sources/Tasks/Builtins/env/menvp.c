/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menvp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:12:11 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/21 11:26:50 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/builtins.h"
#include "../../../../include/executer.h"
#include "../../../../include/read.h"

void	m_envp(int *status, char **menvp)
{
	int	i;

	if (!menvp)
		return ;
	i = 0;
	while (menvp[i])
	{
		if (ft_strchr(menvp[i], '='))
			ft_putendl_fd(menvp[i], 1);
		i++;
	}
	*status = 0;
}

void	print_export(char **dupped)
{
	char	**parsed;
	int		i;

	i = -1;
	while (dupped[++i])
	{
		if (!ft_strncmp(dupped[i], "_=", 2))
			continue ;
		parsed = parse_for_export(dupped[i]);
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(parsed[0], 1);
		if (parsed[1])
		{
			ft_putstr_fd(parsed[1], 1);
			ft_putstr_fd("\"", 1);
			if (parsed[2])
				ft_putstr_fd(parsed[2], 1);
			ft_putendl_fd("\"", 1);
		}
		else
			ft_putendl_fd("", 1);
		clear(parsed);
	}
	clear(dupped);
}

static void	export_value(char ***menvp, char *value)
{
	char	**parsed;

	parsed = parse_for_export(value);
	if (menvp_lookup(parsed[0], *menvp) != -1)
	{
		if (!parsed[1])
			return (free_table(parsed));
		if (parsed[1] && parsed[1][0] == '=')
			export_operation(menvp, value, parsed, 0);
		else if (parsed[1][0] == '+')
			concat_export(menvp, parsed);
	}
	else if (parsed[2])
		export_operation(menvp, NULL, parsed, 1);
	else if (parsed[1] && !parsed[2])
		export_operation(menvp, NULL, parsed, 2);
	else
		*menvp = export_to_menvp(parsed[0], *menvp);
	return (free_table(parsed));
}

void	m_export(int *status, char ***menvp, char *value)
{
	char	**dupped;

	if (!*menvp)
		return ;
	if (!value)
	{
		dupped = setup_menvp(*menvp);
		str_sort(dupped);
		return (print_export(dupped));
	}
	if (is_valid_env_format(value))
		return (export_value(menvp, value));
	if (!exp_is_protected(value))
		m_export_error(status, value);
}

void	m_unset(int *status, char ***menvp, char *value)
{
	char	**parsed;

	*status = 0;
	if (!value || !*menvp)
		return ;
	if (exp_is_protected(value))
		return ;
	parsed = parse_for_export(value);
	if (parsed[1])
	{
		clear(parsed);
		return ;
	}
	if (menvp_lookup(parsed[0], *menvp) != -1)
	{
		*menvp = unset_from_menvp(parsed[0], *menvp);
		if (!*menvp)
			*status = 2;
		clear(parsed);
		return ;
	}
	clear(parsed);
}
