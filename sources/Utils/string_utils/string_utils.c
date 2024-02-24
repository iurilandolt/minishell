/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:37:46 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/24 17:48:43 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"

size_t	ft_strlen(const char *s)
{
	size_t	pos;

	pos = 0;
	while (*s++)
		pos++;
	return (pos);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	if (n == 0)
		return (0);
	while ((*str1 || *str2) && (n > 1) && (*str1 == *str2))
	{
		str1++;
		str2++;
		n--;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (*(src + i) && size && i < size - 1)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	if (size - i != 0)
		*(dest + i) = '\0';
	return (ft_strlen(src));
}

char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*dest;
	size_t	len;
	int		i;
	int		j;

	if (!str1 || !str2)
		return (NULL);
	len = ft_strlen(str1) + ft_strlen(str2);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = -1;
	j = 0;
	while (*(str1 + ++i))
		*(dest + i) = *(str1 + i);
	while (str2[j])
		*(dest + i++) = *(str2 + j++);
	*(dest + i) = '\0';
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		*((char *)dest + i) = *((const char *)src + i);
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *str)
{
	char	*dest;
	size_t	size;

	size = ft_strlen(str) + 1;
	dest = (char *)malloc(sizeof(char) * size);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, str, size);
	return (dest);
}
