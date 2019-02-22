/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_width.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 17:58:23 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/02/16 16:44:06 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_width		*init_width(void)
{
	t_width	*width;

	if (!(width = (t_width *)malloc(sizeof(t_width))))
		return (NULL);
	width->w_group_name = 0;
	width->w_major = 0;
	width->w_minor = 0;
	width->w_num_links = 0;
	width->w_size = 0;
	width->w_user_name = 0;
	return (width);
}

void		fill_width(t_arg_list *head, t_width *width, int *has_spec)
{
	while (head)
	{
		if (width->w_num_links < head->stat.st_nlink)
			width->w_num_links = head->stat.st_nlink;
		head->w_user_name = ft_strlen(getpwuid(head->stat.st_uid)->pw_name);
		head->w_group_name = ft_strlen(getgrgid(head->stat.st_gid)->gr_name);
		if (width->w_user_name < head->w_user_name)
			width->w_user_name = head->w_user_name;
		if (width->w_group_name < head->w_group_name)
			width->w_group_name = head->w_group_name;
		if (S_ISCHR(head->stat.st_mode) || S_ISBLK(head->stat.st_mode))
		{
			*has_spec = 1;
			if (width->w_major < major(head->stat.st_rdev))
				width->w_major = major(head->stat.st_rdev);
			if (width->w_minor < minor(head->stat.st_rdev))
				width->w_minor = minor(head->stat.st_rdev);
		}
		else if (width->w_size < head->stat.st_size)
			width->w_size = head->stat.st_size;
		head = head->next;
	}
}

t_width		*get_width(t_arg_list *head)
{
	t_width	*width;
	int		has_spec;

	width = init_width();
	has_spec = 0;
	fill_width(head, width, &has_spec);
	width->w_num_links = get_number_rank(width->w_num_links);
	width->w_size = get_number_rank(width->w_size);
	if (has_spec)
	{
		width->w_major = get_number_rank(width->w_major) + 1;
		width->w_minor = get_number_rank(width->w_minor);
		if (width->w_size < (width->w_major + width->w_minor + 2))
			width->w_size = (width->w_major + width->w_minor + 2);
		else if (width->w_major < width->w_size - width->w_minor - 2)
			width->w_major = width->w_size - width->w_minor - 2;
	}
	return (width);
}
