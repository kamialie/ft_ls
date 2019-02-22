/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 13:49:41 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/02/20 20:17:11 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_usage(char c)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd(
		"\nusage: ./ft_ls [-ACGRacfglrtux1] [file ...]", 2);
}

static void	check_format_flags(t_bits *flags, char ch)
{
	if (ch == 'l')
	{
		flags->c_upper = 0;
		flags->x = 0;
		flags->one = 0;
	}
	else if (ch == '1')
	{
		flags->c_upper = 0;
		flags->l = 0;
		flags->x = 0;
	}
	else if (ch == 'C')
	{
		flags->l = 0;
		flags->x = 0;
		flags->one = 0;
	}
	else if (ch == 'x')
	{
		flags->c_upper = 0;
		flags->l = 0;
		flags->one = 0;
	}
}

static void	check_excluded_flags(t_value *value, t_bits *flags,
											char ch, size_t n)
{
	if (n < 32)
		value->a |= (0x1 << n);
	else
		value->b |= (0x1 << (n - 32));
	if (ch == 'g')
	{
		ch = 'l';
		flags->l = 1;
	}
	check_format_flags(flags, ch);
	if (ch == 'f')
		flags->a = 1;
	else if (ch == 'c')
		flags->u = 0;
	else if (ch == 'u')
		flags->c = 0;
}

/*
** valid = "ABCFGHLOPRSTUW@abcdefghiklmnopqrstuwx1-";
*/

void		get_flags(char *line, t_value *value, t_bits *flags)
{
	char	c;
	char	*valid;
	char	*p;
	size_t	n;

	valid = "A-C-G----R-----a-c--fg---l-----r-tu-x1-";
	while ((c = *(++line)))
	{
		if ((p = ft_strchr(valid, c)) == NULL)
		{
			print_usage(c);
			exit(1);
		}
		n = p - valid;
		check_excluded_flags(value, flags, c, n);
	}
	if (!isatty(1))
		flags->g_upper = 0;
}
