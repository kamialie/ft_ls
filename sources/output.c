/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 10:35:32 by rgyles            #+#    #+#             */
/*   Updated: 2019/02/20 17:43:27 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_name(t_arg_list *head, t_bits *flags)
{
	if (flags->g_upper)
		color_output(head->file_name, head->stat.st_mode, head->file_name_len);
	else
		write(1, head->file_name, head->file_name_len);
	if (S_ISLNK(head->stat.st_mode) && flags->l)
	{
		ft_putstr(" -> ");
		write(1, head->source_name, head->source_name_len);
	}
	write(1, "\n", 1);
}

void	print_flag_one(t_arg_list *head, t_bits *flags)
{
	while (head != NULL)
	{
		print_name(head, flags);
		head = head->next;
	}
}

void	ft_write(char *str, size_t len, int print)
{
	static char		*line;
	static size_t	i;

	if (!line)
	{
		line = (char *)malloc(sizeof(char) * (LINE_SIZE + 1));
		ft_bzero(line, LINE_SIZE + 1);
		i = 0;
	}
	if (print)
		write(1, line, i);
	else
	{
		while (i + len > LINE_SIZE)
		{
			ft_memmove(line + i, str, LINE_SIZE - i);
			len -= LINE_SIZE - i;
			str += LINE_SIZE - i;
			write(1, line, LINE_SIZE);
			i = 0;
			ft_bzero(line, LINE_SIZE);
		}
		ft_memmove(line + i, str, len);
		i += len;
	}
}

void	output(t_arg_list *head, t_bits *flags)
{
	t_width	*width;
	size_t	lst_size;

	if (head == NULL)
		return ;
	lst_size = get_list_size(head);
	width = (flags->l) ? get_width(head) : NULL;
	if (flags->l)
		while (head != NULL)
		{
			print_with_flag_l(head, width, flags);
			print_name(head, flags);
			head = head->next;
		}
	else if (flags->one)
		print_flag_one(head, flags);
	else
		print_by_column(head, flags, lst_size);
	free(width);
}
