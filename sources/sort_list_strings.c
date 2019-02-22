/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list_strings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 17:35:42 by rgyles            #+#    #+#             */
/*   Updated: 2019/02/11 14:01:25 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			extract_structure(t_arg_list **head, t_arg_list *limit)
{
	t_arg_list	*head_tmp;
	t_arg_list	*current;

	head_tmp = *head;
	if (head_tmp == limit)
		*head = head_tmp->next;
	else
	{
		current = head_tmp->next;
		while (current != limit)
		{
			head_tmp = current;
			current = current->next;
		}
		head_tmp->next = current->next;
	}
}

static t_arg_list	*get_limit(t_arg_list **head)
{
	int			cmp;
	t_arg_list	*limit;
	t_arg_list	*tmp_head;

	tmp_head = *head;
	limit = tmp_head;
	if (tmp_head->next != NULL)
	{
		tmp_head = tmp_head->next;
		while (tmp_head != NULL)
		{
			cmp = ft_strcmp(limit->file_name, tmp_head->file_name);
			if (cmp > 0)
				limit = tmp_head;
			tmp_head = tmp_head->next;
		}
		extract_structure(head, limit);
	}
	limit->next = NULL;
	return (limit);
}

void				sort_list_strings(t_arg_list **head)
{
	t_arg_list	*current;
	t_arg_list	*sorted;

	sorted = NULL;
	current = *head;
	while (current->next != NULL)
		arg_list_push_back(&sorted, get_limit(&current));
	arg_list_push_back(&sorted, current);
	*head = sorted;
}
