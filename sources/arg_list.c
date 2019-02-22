/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 18:46:40 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/02/20 19:08:41 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t		get_list_size(t_arg_list *head)
{
	size_t	list_size;

	list_size = 0;
	while (head)
	{
		head = head->next;
		list_size++;
	}
	return (list_size);
}

t_arg_list	*init_arg_element(char *path, char *d_name)
{
	t_arg_list	*lst;
	char		buf[MAX_PATH_LEN];

	if (!(lst = (t_arg_list *)malloc(sizeof(t_arg_list))))
		return (NULL);
	lst->next = NULL;
	lst->source_name = NULL;
	lst->file_name = NULL;
	if (d_name != NULL)
	{
		lst->file_name = ft_strdup_len_len(d_name, &lst->file_name_len,
													&lst->print_file_name_len);
		lst->path = cat_path(path, &lst->path_len, d_name, lst->file_name_len);
	}
	else
		lst->path = ft_strdup_len(path, &lst->path_len);
	lstat(lst->path, &lst->stat);
	if (S_ISLNK(lst->stat.st_mode))
	{
		ft_bzero(buf, MAX_PATH_LEN);
		readlink(lst->path, buf, MAX_PATH_LEN);
		lst->source_name = ft_strdup_len(buf, &lst->source_name_len);
	}
	return (lst);
}

int			arg_list_push_back(t_arg_list **head, t_arg_list *new_lst)
{
	t_arg_list	*tmp;

	if (!new_lst)
		return (free_arg_list(*head));
	if (*head == NULL)
	{
		*head = new_lst;
		return (0);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_lst;
	return (0);
}

t_arg_list	*create_arg_list(char **av)
{
	t_arg_list	*head;
	t_arg_list	*tmp;

	head = NULL;
	while (*av)
	{
		tmp = init_arg_element(*av, NULL);
		tmp->file_name = ft_strdup_len(*av, &tmp->file_name_len);
		if (arg_list_push_back(&head, tmp))
			exit(1);
		av++;
	}
	return (head);
}
