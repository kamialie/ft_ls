/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 14:37:58 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/02/20 20:03:18 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	check_elem(t_arg_list *head)
{
	if ((S_ISDIR(head->stat.st_mode))
		&& !(ft_strequ(head->file_name, "."))
		&& !(ft_strequ(head->file_name, "..")))
	{
		ft_putchar('\n');
		ft_putstr(head->path);
		ft_putendl(":");
		if ((head->dp = opendir(head->path)) == NULL)
		{
			ft_putstr_fd("ft_ls: ", 2);
			perror(head->file_name);
		}
		else
			return (1);
	}
	return (0);
}

void		sort_and_print(t_arg_list **head, t_bits *flags)
{
	if (!(flags->f))
	{
		if (*head)
			sort_list_strings(head);
		if (flags->t)
			sort_list(head, flags);
	}
	if (flags->r)
		*head = reverse_list(*head);
	if (flags->l)
	{
		ft_putstr("total ");
		ft_putnbr_lli(get_total_blocks(*head));
		write(1, "\n", 1);
	}
	output(*head, flags);
}

void		handle_dir(t_arg_list *elem, t_bits *flags)
{
	t_arg_list		*head;
	t_arg_list		*tmp;
	struct dirent	*dirent;

	head = NULL;
	while ((dirent = readdir(elem->dp)) != NULL)
	{
		if (!(flags->a) && !(flags->a_upper) && *(dirent->d_name) == '.')
			continue ;
		else if (!(flags->a) && flags->a_upper &&
		(ft_strequ(dirent->d_name, ".") || ft_strequ(dirent->d_name, "..")))
			continue ;
		arg_list_push_back(&head, init_arg_element(elem->path, dirent->d_name));
	}
	(void)closedir(elem->dp);
	sort_and_print(&head, flags);
	tmp = head;
	if (flags->r_upper)
		while (tmp)
		{
			if (check_elem(tmp))
				handle_dir(tmp, flags);
			tmp = tmp->next;
		}
	free_arg_list(head);
}

void		file_check(t_arg_list *head, t_bits *flags)
{
	t_arg_list	*reg_files;
	t_arg_list	*tmp;

	reg_files = NULL;
	while (head != NULL)
	{
		if ((head->dp = opendir(head->path)) == NULL)
		{
			if (errno == ENOTDIR)
			{
				tmp = init_arg_element(".", head->path);
				arg_list_push_back(&reg_files, tmp);
			}
			else if (errno == EACCES)
				perror(head->path);
			else
			{
				ft_putstr_fd("ft_ls: ", 2);
				perror(head->path);
			}
		}
		head = head->next;
	}
	output(reg_files, flags);
}

void		handle(t_arg_list *head, t_bits *flags)
{
	int	flag;

	flag = (head->next != NULL) ? 1 : 0;
	file_check(head, flags);
	while (head != NULL)
	{
		if (head->dp != NULL)
		{
			if (flag)
			{
				ft_putchar('\n');
				ft_putstr(head->path);
				ft_putendl(":");
			}
			handle_dir(head, flags);
		}
		head = head->next;
	}
}
