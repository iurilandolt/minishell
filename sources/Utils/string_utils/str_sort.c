/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:41:05 by rlandolt          #+#    #+#             */
/*   Updated: 2024/03/18 16:27:45 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/builtins.h"
#include "../../../include/executer.h"

void	str_swap(char **a, char **b)
{
	char *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	str_sort(char **arr)
{
	int	size;
	int	i;
	int	j;

	size = split_size(arr);
	if (size < 2)
		return ;
	i = 0;
	while(i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(arr[j], arr[j + 1], ft_strlen(arr[j])) > 0)
				str_swap(&arr[j], &arr[j + 1]);
			j++;
		}
		i++;
	}
}
