/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 09:40:27 by rgyles            #+#    #+#             */
/*   Updated: 2019/02/19 19:31:45 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	handle_flags(char ***av, t_flags *flags)
{
	while (*(++(*av)) && ***av == '-')
	{
		get_flags(**av, &flags->value, &flags->bits);
		if ((**av)[1] == '-')
		{
			++(*av);
			break ;
		}
	}
}

int			main(int ac, char **av)
{
	t_flags		flags;
	t_arg_list	*head;

	if (ac > 1)
	{
		flags.value.a = 0;
		flags.value.b = 0;
		handle_flags(&av, &flags);
		if (!*av)
			head = init_arg_element(".", NULL);
		else
		{
			ft_sort_strarray(av, 1);
			head = create_arg_list(av);
		}
	}
	else
		head = init_arg_element(".", NULL);
	handle(head, &flags.bits);
	free_arg_list(head);
	return (0);
}
