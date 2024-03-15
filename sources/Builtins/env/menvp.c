/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menvp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:12:11 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/15 17:32:55 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/executer.h"
#include "../../../include/read.h"

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

void	print_export(char **menvp)
{
	char **parsed;
	int	i;

	i = 0;
	while(menvp[i])
	{
		parsed = parse_for_export(menvp[i]);
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
		i++;
	}
}

void	m_export(int *status, char ***menvp, char *value)
{
	char	**parsed;

	if (!*menvp)
		return ;
	if (!value)
		return (print_export(*menvp));
	if (is_valid_env_format(value))
	{
		parsed = parse_for_export(value);
		if (menvp_lookup(parsed[0], *menvp) != -1)
		{
			if (!parsed[1] || parsed[1][0] == '=')
				export_operation(menvp, value, parsed, 0);
			else if (parsed[1][0] == '+')
				concat_export(menvp, parsed);
		}
		else
		{
			if (parsed[2])
				export_operation(menvp, NULL, parsed, 1);
			else if (parsed[1] && !parsed[2])
				export_operation(menvp, NULL, parsed, 2);
			else
				*menvp = export_to_menvp(parsed[0], *menvp);
		}
		clear(parsed);
	}
	*status = 0;
}

void	m_unset(int *status, char ***menvp, char *value)
{
	int		i;

	*status = 0;
	if (!value)
		return ;
	if (!*menvp)
		return ;
	if (!ft_strncmp(value, "_=", 2) || !ft_strncmp(value, "_+=", 3)
		|| (value[0] == '_' && value[1] == '\0')
		|| (value[0] == '_' && value[1] == '='))
		return ;
	i = 0;
	while (menvp[0][i])
	{
		if (ft_strncmp(value, menvp[0][i],
		ft_strlen(value)) == 0 && value[0] != '\0')
		{
			*menvp = unset_from_menvp(value, *menvp);
			if (!*menvp)
				*status = 2;
			return ;
		}
		i++;
	}
}
