/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arg_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 09:38:06 by rgyles            #+#    #+#             */
/*   Updated: 2019/02/11 09:50:43 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			free_arg_list(t_arg_list *head)
{
	t_arg_list	*tmp;

	if (head == NULL)
		return (1);
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->path);
		free(tmp->source_name);
		free(tmp->file_name);
		free(tmp);
	}
	return (1);
}
