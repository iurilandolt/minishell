/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:51:11 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/22 18:56:36 by rcastelo         ###   ########.fr       */
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
int		ambient_variable_expansion(char **string, char **envp);
char	*string_expander(char *string);
char	*string_contracter(char *string);
int		check_analyzer(char *string);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strjoin(char const *str1, char const *str2);

char	**ft_split(const char *str, char c);

int		split_size(char **split);
int		ft_strncmp(const char *str1, const char *str2, size_t n);

void	free_table(char **table);

#endif
