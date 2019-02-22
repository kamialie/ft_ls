/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 20:48:01 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/02/15 20:57:44 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_arg_list	*link_basket(t_arg_list **basket)
{
	int			i;
	t_arg_list	*head;

	i = -1;
	head = NULL;
	while (++i < 16)
	{
		if (basket[i])
			arg_list_push_back(&head, basket[i]);
	}
	return (head);
}

int			basket_check(int i, int k, t_arg_list *elem, t_bits *flags)
{
	if (flags->u)
	{
		if (((elem->stat.st_atimespec.tv_sec >> (4 * k)) & 0xF) == 0xF - i)
			return (1);
	}
	else if (((elem->stat.st_mtimespec.tv_sec >> (4 * k)) & 0xF) == 0xF - i)
		return (1);
	return (0);
}

void		sort_pass(t_arg_list **head, t_bits *flags, int k)
{
	int				i;
	t_arg_list		*tmp;
	t_arg_list		*tmp_next;
	t_arg_list		*basket[16];

	tmp = *head;
	i = -1;
	while (++i < 16)
		basket[i] = NULL;
	while (tmp != NULL)
	{
		i = -1;
		tmp_next = tmp->next;
		while (++i < 16)
		{
			if (basket_check(i, k, tmp, flags))
			{
				tmp->next = NULL;
				arg_list_push_back(&basket[i], tmp);
				break ;
			}
		}
		tmp = tmp_next;
	}
	*head = link_basket(basket);
}

int			get_total_bytes(void)
{
	int					i;
	unsigned long int	j;
	unsigned long int	cur_time;

	i = 0;
	j = 0xFFFFFFFFFFFFFFFF;
	cur_time = time(NULL);
	while (i < 16)
	{
		if (!(j & cur_time))
			return (i);
		i++;
		j = j << 4;
	}
	return (i);
}

void		sort_list(t_arg_list **head, t_bits *flags)
{
	int	k;
	int	total_bytes;

	k = 0;
	total_bytes = get_total_bytes();
	while (k < total_bytes)
	{
		sort_pass(head, flags, k);
		k++;
	}
}
