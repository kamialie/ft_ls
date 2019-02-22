/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_by_column.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 17:09:52 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/02/20 17:43:34 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_one_elem_in_row(t_arg_list *elem, t_bits *flags,
										size_t max_file_name)
{
	size_t	len;

	len = elem->print_file_name_len;
	if (flags->g_upper)
		color_output(elem->file_name, elem->stat.st_mode, elem->file_name_len);
	else
		write(1, elem->file_name, elem->file_name_len);
	if (flags->g_upper)
		while (len++ < max_file_name)
			write(1, " ", 1);
	else
		while (len < max_file_name)
		{
			len += 8;
			write(1, "\t", 1);
		}
}

void		print_with_c_upper_flag(t_arg_list **arr, t_bits *flags,
						size_t list_size, size_t max_file_name)
{
	int				num_col;
	size_t			jump;
	size_t			i;
	size_t			row;

	num_col = get_num_column(max_file_name);
	jump = list_size / num_col;
	if (list_size % num_col)
		jump++;
	row = 0;
	while (row < jump)
	{
		i = row;
		while (i < list_size)
		{
			print_one_elem_in_row(arr[i], flags, max_file_name);
			i += jump;
		}
		write(1, "\n", 1);
		row++;
	}
}

void		print_with_x_flag(t_arg_list **arr, t_bits *flags,
						size_t list_size, size_t max_file_name)
{
	int				num_col;
	size_t			i;
	int				check_new_line;

	i = 0;
	num_col = get_num_column(max_file_name);
	while (i < list_size)
	{
		print_one_elem_in_row(arr[i], flags, max_file_name);
		i++;
		check_new_line = 0;
		if (i % num_col == 0)
		{
			write(1, "\n", 1);
			check_new_line = 1;
		}
	}
	if (!check_new_line)
		write(1, "\n", 1);
}

void		print_by_column(t_arg_list *head, t_bits *flags, size_t list_size)
{
	t_arg_list		**arr;
	size_t			max_file_name;

	max_file_name = get_max_file_name(head, flags->g_upper);
	arr = init_array_of_list(head, list_size);
	if (flags->x)
		print_with_x_flag(arr, flags, list_size, max_file_name);
	else
		print_with_c_upper_flag(arr, flags, list_size, max_file_name);
	free(arr);
}
