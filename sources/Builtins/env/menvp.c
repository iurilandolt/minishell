/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menvp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:12:11 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/05 13:55:13 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/executer.h"
#include "../../../include/read.h"

void	m_envp(char **menvp)
{
	int	i;

	if (!menvp)
		return ;
	i = 0;
	while (menvp[i])
	{
		if (ft_strchr(menvp[i], '='))
			printf("%s\n", menvp[i]);
		i++;
	}
}

void	m_export(char ***menvp, char *value) // int fd
{
	int		i;
	char	**parsed;

	if (!*menvp)
		return ;
	if (!value)
	{
		i = 0;
		while (menvp[0][i])
			printf("declare -x %s\n", menvp[0][i++]); // putstr_fd(str, fd)
	}
	else
	{
		if (is_valid_env_format(value))
		{
			parsed = parse_for_export(value);
			if (menvp_lookup(parsed[0], *menvp))
			{
				if (!parsed[1] || parsed[1][0] == '=')
				{
					*menvp = unset_from_menvp(parsed[0], *menvp);
					*menvp = export_to_menvp(value, *menvp);
				}
				else if (parsed[1][0] == '+')
				{
					char **old_value;
					char *new_value;
					char *tmp;

					old_value = parse_for_export((*menvp)[menvp_lookup(parsed[0], *menvp)]);
					new_value = ft_strjoin(old_value[0], "=");
					tmp = ft_strjoin(new_value, old_value[2]);
					free(new_value);
					new_value = ft_strjoin(tmp, parsed[2]);

					*menvp = unset_from_menvp(parsed[0], *menvp);
					*menvp = export_to_menvp(new_value, *menvp);

					free(new_value);
					free(tmp);
					clear(old_value);
				}
			}
			clear(parsed);
		}
	}
}

void	m_unset(char ***menvp, char *value) // int fd
{
	int		i;

	if (!value)
		return ;
	if (!*menvp)
		return ;
	i = 0;
	while (menvp[0][i])
	{
		if (ft_strncmp(value, menvp[0][i], ft_strlen(value)) == 0 && value[0] != '\0')
		{
			*menvp = unset_from_menvp(value, *menvp);
			if (!*menvp)
				perror("**unset error\n");
			return ;
		}
		i++;
	}
}
