/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_for_output.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 23:30:12 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/02/16 23:31:25 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			get_num_column(int max_file_name)
{
	struct winsize	ws;
	int				num_col;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	num_col = (int)ws.ws_col / (max_file_name);
	num_col = (num_col) ? num_col : 1;
	return (num_col);
}

t_arg_list	**init_array_of_list(t_arg_list *head, size_t list_size)
{
	t_arg_list	**arr;
	int			i;

	arr = (t_arg_list **)malloc(sizeof(t_arg_list *) * (list_size + 1));
	ft_bzero(arr, sizeof(t_arg_list *) * (list_size + 1));
	i = 0;
	while (head != NULL)
	{
		arr[i] = head;
		head = head->next;
		i++;
	}
	return (arr);
}
