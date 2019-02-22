/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_with_flag_l.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:12:57 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/02/16 16:41:27 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_major(t_arg_list *head, t_width *width)
{
	head->w_major = get_number_rank(major(head->stat.st_rdev));
	head->w_minor = get_number_rank(minor(head->stat.st_rdev));
	write(1, "   ", 2);
	while (width->w_major > head->w_major++)
		write(1, " ", 1);
	ft_putnbr_lli(major(head->stat.st_rdev));
	write(1, ", ", 2);
	while (width->w_minor > head->w_minor++)
		write(1, " ", 1);
	ft_putnbr_lli(minor(head->stat.st_rdev));
}

void	print_size(t_arg_list *head, t_width *width)
{
	head->w_size = get_number_rank(head->stat.st_size);
	write(1, "  ", 2);
	while (width->w_size > head->w_size++)
		write(1, " ", 1);
	ft_putnbr_lli(head->stat.st_size);
}

void	print_user_name(t_arg_list *head, t_width *width)
{
	ft_putstr(getpwuid(head->stat.st_uid)->pw_name);
	while (width->w_user_name > head->w_user_name++)
		write(1, " ", 1);
	write(1, "  ", 2);
}

void	print_with_flag_l(t_arg_list *head, t_width *width, t_bits *flags)
{
	head->w_num_links = get_number_rank(head->stat.st_nlink);
	head->w_user_name = ft_strlen(getpwuid(head->stat.st_uid)->pw_name);
	head->w_group_name = ft_strlen(getgrgid(head->stat.st_gid)->gr_name);
	get_permissions(head->stat.st_mode, head->path);
	write(1, " ", 1);
	while (width->w_num_links > head->w_num_links++)
		write(1, " ", 1);
	ft_putnbr(head->stat.st_nlink);
	write(1, " ", 1);
	if (!(flags->g))
		print_user_name(head, width);
	ft_putstr(getgrgid(head->stat.st_gid)->gr_name);
	while (width->w_group_name > head->w_group_name++)
		write(1, " ", 1);
	if (S_ISCHR(head->stat.st_mode) || S_ISBLK(head->stat.st_mode))
		print_major(head, width);
	else
		print_size(head, width);
	write(1, " ", 1);
	if (flags->t && flags->u)
		get_time(head->stat.st_atimespec.tv_sec);
	else
		get_time(head->stat.st_mtimespec.tv_sec);
	write(1, " ", 1);
}
