/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:23:14 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/15 17:22:52 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <sys/stat.h>
# include <dirent.h>
# include "executer.h"

// CD
typedef enum e_sysdir
{
	HOME,
	PWD,
	OLDPWD,

}	t_sysdir;


char	*set_directory(t_sysdir dir, char **menvp);
void	change_dir(t_session *session, char *path, int *status);
void	cd_path(t_session *session, char *path);
void	cd_oldpwd(t_session *session);
void	cd_home(t_session *session);

// ENV, EXPORT & UNSET
char	**setup_menvp(char **envp);
void	m_envp(int *status, char **menvp);
void	m_export(int *status, char ***menvp, char *value);
char	**export_to_menvp(char *add, char **menvp);
void	m_unset(int *status, char ***menvp, char *value);
char 	**unset_from_menvp(char *del, char **menvp);


int		is_valid_env_format(const char *str);
char	**parse_for_export(char *value);
int		menvp_lookup(char *value, char **menvp);
void	concat_export(char ***menvp, char **parsed);
void	export_operation(char ***menvp, char* value, char **parsed, int op);
void	update_shlvl(t_session *session);
// PWD
void	mpwd(int *status);
// echo
void	echo(char **cmd, int *status);

void	m_exit(t_session *session, int taskn);

#endif
