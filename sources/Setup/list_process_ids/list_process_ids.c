/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_process_ids.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:58:20 by rcastelo          #+#    #+#             */
/*   Updated: 2024/03/12 17:04:27 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/read.h"
#include "../../../include/token.h"
#include "../../../include/executer.h"

int	*list_process_ids(int ntasks)
{
	int	*list_p_ids;

	list_p_ids = malloc(ntasks * sizeof(int));
	if (!list_p_ids)
		return (perror(0), (int *)0);
	while (ntasks--)
		list_p_ids[ntasks] = 0;
	return (list_p_ids);
}