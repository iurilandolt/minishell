/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:51:11 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/06 16:32:25 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

char	*get_next_line(int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ambient_variable_expansion(int status, char **string, char **envp);
char	*string_expander(char *string);
char	*string_contracter(char *string);

char *expand_tilde(char *cmd);

int		check_analyzer(char *string);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strjoin(char const *str1, char const *str2);
char	*ft_strchr(const char *str, int c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strdup(const char *str);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);

char	**ft_split(const char *str, char c);
void	*clear(char **array);
int		split_size(char **split);

void	free_table(char **table);
void	free_table_n(void **table, int ntasks);

// quote_split.h
typedef struct s_qt
{
	int	qt;
	int	qts;
}	t_qt;

char	**quote_split(char const *s, char c);
void	clean_quotes(char **string);


#endif
