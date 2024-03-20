/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbin_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:35:31 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/20 22:25:42 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_simple(char *cmd)
{
	int	i;

	i = -1;
	if (cmd[0] == '/')
		return (0);
	if (*cmd && cmd[0] == '.' && cmd[1] == '/')
		return (0);
	if (*cmd && cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
		return (0);
	while (cmd[++i])
	{
		if (cmd[i] == '/')
			return (0);
	}
	return (1);
}
