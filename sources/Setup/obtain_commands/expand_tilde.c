/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:01:45 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/25 14:43:37 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/token.h"
#include "../../../include/read.h"
#include "../../../include/executer.h"

char *extract_tilde(char *cmd)
{
	int		i;
	char	*extracted;

	i = 0;
	if ((cmd[i] == '~') || (cmd[i] == '~' && cmd[i + 1] == '/')
						|| (cmd[i] == '~' && cmd[i + 1] == '\0'))
		i++;
	extracted = ft_strdup(&cmd[i]);
	free(cmd);
	return (extracted);
}

char *expand_tilde(char *cmd)
{
	char *home;
	char *swap;

	if (cmd[0] == '~' || (cmd[0] == '~' && cmd[1] == '/'))
	{
		home = getenv("HOME");
		if (!home)
			return (cmd);
		cmd = extract_tilde(cmd);
		swap = ft_strjoin(home, cmd);
		free(cmd);
		return (swap);
	}
	return (cmd);
}

