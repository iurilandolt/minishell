/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:23:14 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/06 18:25:08 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <sys/stat.h>
# include <dirent.h>

// CD & PWD
typedef struct s_cd
{
	char	*home;
	char	*pwd;
	char	*oldpwd;
}	t_cd;

void	setup_cd(t_cd *cd, char **envp);
void	change_dir(t_cd *cd, char *path);
void	free_cd(t_cd *cd);
// ENV, EXPORT & UNSET
char	**setup_menvp(char **envp);
void	m_envp(char **menvp);
void	m_export(char ***menvp, char *value);
char	**export_to_menvp(char *add, char **menvp);
void	m_unset(char ***menvp, char *value);
char 	**unset_from_menvp(char *del, char **menvp);


int		is_valid_env_format(const char *str);
char	**parse_for_export(char *value);
int		menvp_lookup(char *value, char **menvp);
void	concat_export(char ***menvp, char **parsed);
void	export_operation(char ***menvp, char* value, char **parsed, int op);
// PWD
void	mpwd(void);
// echo
void	echo(char **cmd); //where are you?


#endif
