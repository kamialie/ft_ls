/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 10:39:46 by rgyles            #+#    #+#             */
/*   Updated: 2019/02/20 17:09:16 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	set_color_for_reg_files(mode_t mode)
{
	if (mode & S_IXUSR || mode & S_IXGRP || mode & S_IXOTH)
		write(1, "\033[31m", 5);
	if (mode & S_ISUID && mode & S_IXUSR)
		write(1, "\033[41;30m", 8);
	else if (mode & S_ISGID && mode & S_IXGRP)
		write(1, "\033[46;30m", 8);
}

void		color_output(char *str, mode_t mode, size_t file_name_len)
{
	if (S_ISREG(mode))
		set_color_for_reg_files(mode);
	else if (S_ISDIR(mode))
	{
		if (mode & S_ISVTX)
			write(1, "\033[42;30m", 8);
		else
			write(1, "\033[34m", 5);
	}
	else if (S_ISLNK(mode))
		write(1, "\033[35m", 5);
	else if (S_ISCHR(mode))
		write(1, "\033[43;34m", 8);
	else if (S_ISBLK(mode))
		write(1, "\033[46;34m", 8);
	else if (S_ISSOCK(mode))
		write(1, "\033[32m", 5);
	else if (S_ISFIFO(mode))
		write(1, "\033[33m", 5);
	write(1, str, file_name_len);
	write(1, "\033[0m", 4);
}
