/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bin_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:50:16 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/21 12:16:28 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/token.h"
#include "../../../include/read.h"
#include "../../../include/executer.h"
#include "../../../include/builtins.h"

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
	if (!*cmd)
		return (cmd);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (cmd);
	tool.paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (*(tool.paths + i))
	{
		path_to_program(&tool, cmd, i);
		if (access(tool.program, F_OK) == 0)
		{
			clear(tool.paths);
			free(cmd);
			return (tool.program);
		}
		free(tool.program);
		i++;
	}
	return (clear(tool.paths), cmd);
}

void	error_message(char *cmd, char *string)
{
	int		size;
	char	*message;

	size = 0;
	message = ft_strjoin(cmd, string);
	while (message[size])
		size++;
	write(2, message, size);
	free(message);
}

int	cmd_is_dir(t_session *session, int taskn, char *cmd)
{
	struct stat	cmd_stat;

	if (stat(cmd, &cmd_stat) == 0 && !is_simple(cmd))
		return (S_ISDIR(cmd_stat.st_mode));
	else if (lstat(cmd, &cmd_stat) == 0)
		return (S_ISLNK(cmd_stat.st_mode));
	else if (!is_simple(cmd))
	{
		error_message(cmd, ": No such file or directory.\n");
		exit_safe(session, taskn, 127);
	}
	return (-1);
}

void	link_cmd_codes(t_session *session, int taskn, char *cmd)
{
	if (cmd_is_dir(session, taskn, cmd) > 0)
	{
		error_message(cmd, ": Is a directory.\n");
		exit_safe(session, taskn, 126);
	}
	if (access(cmd, F_OK) != 0 || is_simple(cmd))
	{
		error_message(cmd, ": command not found\n");
		exit_safe(session, taskn, 127);
	}
	if (access(cmd, X_OK) != 0)
	{
		perror(cmd);
		exit_safe(session, taskn, 126);
	}
}
