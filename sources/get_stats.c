/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 09:41:19 by rgyles            #+#    #+#             */
/*   Updated: 2019/02/11 22:30:15 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

long long int		get_total_blocks(t_arg_list *head)
{
	long long int	total;

	total = 0;
	while (head)
	{
		total += head->stat.st_blocks;
		head = head->next;
	}
	return (total);
}

void				get_time(long int time_stat)
{
	int		i;
	char	*file_date;
	char	output[13];

	i = -1;
	file_date = ctime(&time_stat);
	output[++i] = file_date[4];
	output[++i] = file_date[5];
	output[++i] = file_date[6];
	output[++i] = ' ';
	output[++i] = file_date[8];
	output[++i] = file_date[9];
	output[++i] = ' ';
	if (time(NULL) - time_stat > SIX_MONTH)
	{
		i++;
		output[i] = file_date[i];
		while (++i < 12)
			output[i] = file_date[i + 12];
	}
	else
		while (++i < 12)
			output[i] = file_date[i + 4];
	output[12] = '\0';
	ft_putstr(output);
}

static char			get_file_type(mode_t mode_val)
{
	if (S_ISREG(mode_val))
		return ('-');
	else if (S_ISDIR(mode_val))
		return ('d');
	else if (S_ISLNK(mode_val))
		return ('l');
	else if (S_ISBLK(mode_val))
		return ('b');
	else if (S_ISCHR(mode_val))
		return ('c');
	else if (S_ISFIFO(mode_val))
		return ('p');
	else if (S_ISSOCK(mode_val))
		return ('s');
	else
		return ('-');
}

char				get_acl(char *path)
{
	acl_t		acl;
	acl_entry_t	entry;
	ssize_t		xattr;
	char		c;

	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) == -1)
		acl = NULL;
	xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	c = (xattr > 0) ? '@' : ' ';
	c = (acl != NULL) ? '+' : c;
	acl_free(acl);
	return (c);
}

void				get_permissions(mode_t mode_val, char *path)
{
	char	result[12];

	result[0] = get_file_type(mode_val);
	result[1] = (mode_val & S_IRUSR) ? 'r' : '-';
	result[2] = (mode_val & S_IWUSR) ? 'w' : '-';
	result[3] = (mode_val & S_IXUSR) ? 'x' : '-';
	result[4] = (mode_val & S_IRGRP) ? 'r' : '-';
	result[5] = (mode_val & S_IWGRP) ? 'w' : '-';
	result[6] = (mode_val & S_IXGRP) ? 'x' : '-';
	result[7] = (mode_val & S_IROTH) ? 'r' : '-';
	result[8] = (mode_val & S_IWOTH) ? 'w' : '-';
	result[9] = (mode_val & S_IXOTH) ? 'x' : '-';
	result[10] = get_acl(path);
	if (mode_val & S_ISUID)
		result[3] = (result[3] == 'x') ? 's' : 'S';
	if (mode_val & S_ISGID)
		result[6] = (result[6] == 'x') ? 's' : 'S';
	if (mode_val & S_ISVTX)
		result[9] = (result[9] == 'x') ? 't' : 'T';
	result[11] = '\0';
	ft_putstr(result);
}
