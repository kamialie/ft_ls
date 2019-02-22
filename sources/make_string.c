/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 17:40:00 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/02/20 15:21:49 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*cat_path(char *path, size_t *path_len, char *file_name,
											size_t file_name_len)
{
	char	*new_path;
	size_t	path_len1;

	path_len1 = ft_strlen(path);
	if (path[path_len1 - 1] == '/')
		path_len1--;
	file_name_len = ft_strlen(file_name);
	new_path = (char *)malloc(sizeof(char) * (path_len1 + file_name_len + 2));
	if (path_len1)
		ft_memmove(new_path, path, path_len1);
	new_path[path_len1] = '/';
	ft_memmove(new_path + path_len1 + 1, file_name, file_name_len);
	new_path[path_len1 + file_name_len + 1] = '\0';
	*path_len = path_len1 + file_name_len + 1;
	return (new_path);
}

int		get_max_file_name(t_arg_list *head, int is_upper_g)
{
	size_t	max_file_name;

	max_file_name = 0;
	while (head)
	{
		if (max_file_name < head->file_name_len)
			max_file_name = head->file_name_len;
		head = head->next;
	}
	max_file_name++;
	if (!is_upper_g)
		while (max_file_name % 8)
			max_file_name++;
	return (max_file_name);
}

int		get_number_rank(int nb)
{
	int	i;

	if (nb == 0)
		return (1);
	i = 0;
	while (nb)
	{
		i++;
		nb /= 10;
	}
	return (i);
}
