/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 09:42:02 by rgyles            #+#    #+#             */
/*   Updated: 2019/02/20 17:09:56 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# include <sys/acl.h>
# include "libft.h"
# include <stdio.h>

# define MAX_PATH_LEN 4096
# define LINE_SIZE 500
# define SIX_MONTH 15778463

typedef struct	s_bits
{
	unsigned char	a_upper : 1;
	unsigned char	b_upper : 1;
	unsigned char	c_upper : 1;
	unsigned char	f_upper : 1;
	unsigned char	g_upper : 1;
	unsigned char	h_upper : 1;
	unsigned char	l_upper : 1;
	unsigned char	o_upper : 1;
	unsigned char	p_upper : 1;
	unsigned char	r_upper : 1;
	unsigned char	s_upper : 1;
	unsigned char	t_upper : 1;
	unsigned char	u_upper : 1;
	unsigned char	w_upper : 1;
	unsigned char	at_sign : 1;
	unsigned char	a : 1;
	unsigned char	b : 1;
	unsigned char	c : 1;
	unsigned char	d : 1;
	unsigned char	e : 1;
	unsigned char	f : 1;
	unsigned char	g : 1;
	unsigned char	h : 1;
	unsigned char	i : 1;
	unsigned char	k : 1;
	unsigned char	l : 1;
	unsigned char	m : 1;
	unsigned char	n : 1;
	unsigned char	o : 1;
	unsigned char	p : 1;
	unsigned char	q : 1;
	unsigned char	r : 1;
	unsigned char	s : 1;
	unsigned char	t : 1;
	unsigned char	u : 1;
	unsigned char	w : 1;
	unsigned char	x : 1;
	unsigned char	one : 1;
}				t_bits;

typedef struct	s_value
{
	unsigned int	a;
	unsigned int	b;
}				t_value;

typedef union	u_flags
{
	struct s_value		value;
	struct s_bits		bits;
}				t_flags;

typedef struct	s_arg_list
{
	struct stat			stat;
	DIR					*dp;
	size_t				path_len;
	size_t				file_name_len;
	size_t				print_file_name_len;
	size_t				source_name_len;
	int					w_user_name;
	int					w_group_name;
	int					w_num_links;
	int					w_size;
	int					w_major;
	int					w_minor;
	char				*path;
	char				*source_name;
	char				*file_name;
	struct s_arg_list	*next;
}				t_arg_list;

typedef struct	s_width
{
	int			w_group_name;
	int			w_major;
	int			w_minor;
	int			w_num_links;
	int			w_size;
	int			w_user_name;
}				t_width;

int				arg_list_push_back(t_arg_list **head, t_arg_list *new_lst);
t_arg_list		*create_arg_list(char **av);
int				free_arg_list(t_arg_list *head);
size_t			get_list_size(t_arg_list *head);
t_arg_list		*init_arg_element(char *path, char *d_name);

void			color_output(char *str, mode_t file_mode, size_t file_name_len);

void			sort_list(t_arg_list **head, t_bits *flags);
void			sort_list_strings(t_arg_list **head);
t_arg_list		*reverse_list(t_arg_list *tmp);

void			get_flags(char *line, struct s_value *value, t_bits *flags);

void			handle(t_arg_list *head, t_bits *flags);

void			output(t_arg_list *head, t_bits *flags);

void			get_permissions(mode_t mode_val, char *path);
void			get_time(long int time_stat);
long long int	get_total_blocks(t_arg_list *head);

void			print_by_column(t_arg_list *head, t_bits *flags,
													size_t lst_size);

char			*cat_path(char *path, size_t *path_len, char *file_name,
													size_t file_name_len);
int				get_max_file_name(t_arg_list *head, int is_upper_g);
int				get_number_rank(int nb);

t_width			*get_width(t_arg_list *head);

void			print_with_flag_l(t_arg_list *head, t_width *width,
													t_bits *flags);

int				get_num_column(int max_file_name);
t_arg_list		**init_array_of_list(t_arg_list *head, size_t list_size);

#endif
