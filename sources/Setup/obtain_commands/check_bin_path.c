/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bin_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:50:16 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/23 16:18:55 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/token.h"
#include "../../../include/read.h"


char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!haystack && len == 0)
		return (NULL);
	else if (!haystack[i] && !needle[i])
		return ((char *)haystack);
	while ((haystack[i]) && (i <= len))
	{
		j = 0;
		while ((needle[j]) && (haystack[i + j] == needle[j]) && (i + j < len))
			j++;
		if (!needle[j])
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}

char	*check_bin_path(char **envp, char *cmd)
{
	int		i;
	char	**paths; // could be storeed on instance struct?
	char	*path;
	char	*program;

	i = 0;
	if (access(cmd, F_OK) == 0)
	{
		printf("valid path: %s\n", cmd);
		return (cmd);
	}
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (*(paths + i))
	{
		path = ft_strjoin(paths[i], "/"); // 60 61 62; could be handle by an auxiliar function?
		program = ft_strjoin(path, cmd);
		free(path);
		if (access(program, F_OK | X_OK) == 0)
		{
			clear(paths);
			printf("valid bin: %s\n", program);
			return (program);
		}
		free(program);
		i++;
	}
	printf("command not found: %s\n", cmd);
	return (clear(paths));
}


/*
func() check command.
	check bin path, returns string if directory is valid or bin exists,
	returns null otherwise.
	if null retur code = 127

	if not NULL
	check if is directory or file,
	if directory or bin without permissions -> 126
*/
