/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bin_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:50:16 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/25 12:39:05 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/token.h"
#include "../../../include/read.h"
#include "../../../include/executer.h"

void	path_to_program(t_path_tools *tool, char *cmd, int i)
{
	tool->path = ft_strjoin(tool->paths[i], "/");
	tool->program = ft_strjoin(tool->path, cmd);
	free(tool->path);
}

char	*validate_bin_path(char **envp, char *cmd)
{
	int				i;
	t_path_tools	tool;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	tool.paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (*(tool.paths + i))
	{
		path_to_program(&tool, cmd, i);
		if (access(tool.program, F_OK) == 0)
		{
			clear(tool.paths);
			return (tool.program);
		}
		free(tool.program);
		i++;
	}
	clear(tool.paths);
	return (cmd);
}

int	cmd_is_dir(char *cmd)
{
	struct stat	cmd_stat;

	if (lstat(cmd, &cmd_stat) == 0 || stat(cmd, &cmd_stat) == 0)
		return (S_ISDIR(cmd_stat.st_mode));
	return (-1);
}

int	return_dir_code(char *cmd)
{
	struct stat	cmd_stat;

	if (lstat(cmd, &cmd_stat) == 0 || stat(cmd, &cmd_stat) == 0)
	{
		if (S_ISDIR(cmd_stat.st_mode))
		{
			printf("%s Is a directory.\n", cmd);
			return (126);
		}
	}
	else
	{
		printf("%s : No such file or directory.\n", cmd);
		return (127);
	}
	return (-1);
}

int	link_cmd_codes(char *cmd)
{
	if (!cmd)
		return (127);
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
		return (128);
	}
	else if (access(cmd, X_OK) == 0)
		printf("execeve: %s\n", cmd);
	return (1);
}
