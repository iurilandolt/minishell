/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:26:16 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/09 20:04:36 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/builtins.h"
#include "../../../include/executer.h"
#include "../../../include/read.h"

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
		*menvp = unset_from_menvp(parsed[0], *menvp);
		*menvp = export_to_menvp(tmp, *menvp);
		free(new_value);
	}
	else if (!old_value[2] && parsed[2])
	{
		new_value = ft_strjoin(tmp, parsed[2]);
		*menvp = unset_from_menvp(parsed[0], *menvp);
		*menvp = export_to_menvp(new_value, *menvp);
		free(new_value);
	}
	else if((old_value[0] && !old_value[1]) && parsed[1])
	{
		*menvp = unset_from_menvp(parsed[0], *menvp);
		*menvp = export_to_menvp(tmp, *menvp);
	}
	free(tmp);
	clear(old_value);
}

void	export_operation(char ***menvp, char* value, char **parsed, int op)
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
