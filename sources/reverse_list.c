/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 19:39:30 by rgyles            #+#    #+#             */
/*   Updated: 2019/02/10 19:39:43 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_arg_list	*reverse_list(t_arg_list *tmp)
{
	t_arg_list	*tmp_head;

	if (!tmp)
		return (NULL);
	if (tmp->next == NULL)
		return (tmp);
	else
		tmp_head = reverse_list(tmp->next);
	tmp->next = NULL;
	arg_list_push_back(&tmp_head, tmp);
	return (tmp_head);
}
