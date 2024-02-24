/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bin_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:50:16 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/24 14:42:05 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/token.h"
#include "../../../include/read.h"
#include "../../../include/executer.h"


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

char	*validate_bin_path(char **envp, char *cmd)
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
		if (access(program, F_OK) == 0)
		{
			clear(paths);
			printf("valid path: %s\n", program);
			return (program);
		}
		free(program);
		i++;
	}
	clear(paths);
	return (cmd);
}

int	cmd_is_dir(char *cmd)
{
	if (cmd[0] == '/' && cmd[ft_strlen(cmd) - 1] == '/')
		return (1);
	else
		return (0);
}

int	return_dir_code(char *cmd)
{
	struct stat path_stat;
	int ret;

	ret = stat(cmd, &path_stat);
	if (ret == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			printf("%s Is a directory.\n", cmd);
			return (126);
		}
		return (errno);
	}
	else
	{
		printf("%s Is not a directory.\n", cmd);
		return (127);
	}
}

int link_command(char *cmd)
{
	if (!cmd)
		return (127); // Command not found
	if (cmd_is_dir(cmd))
		return (return_dir_code(cmd));
	if (access(cmd, F_OK) != 0)
	{
		printf("%s : command not found\n", cmd);
		return (127);
	}
	if (access(cmd, X_OK) != 0)
	{
		printf("%s: Permission denied.\n", cmd);
		return (126);
	}
	else if (access(cmd, X_OK) == 0)
		printf("valid bin: %s\n", cmd);
	return (1);
}

