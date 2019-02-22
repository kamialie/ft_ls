# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/10 17:38:22 by dmorgil           #+#    #+#              #
#    Updated: 2019/02/17 15:03:14 by ggwin-go         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls
HEADER=includes/ft_ls.h
SRCS_DIR=./sources
OBJS_DIR=./objects
LIBFT_DIR=./libft
RAW_SRCS=arg_list.c\
	color_output.c\
	free_arg_list.c\
	functions_for_output.c\
	get_flags.c\
	get_stats.c\
	get_width.c\
	handle.c\
	main.c\
	make_string.c\
	output.c\
	print_by_column.c\
	print_with_flag_l.c\
	reverse_list.c\
	sort_list_strings.c\
	sort_list.c
	
RAW_OBJS=$(RAW_SRCS:.c=.o)
SRCS=$(addprefix $(SRCS_DIR)/,$(RAW_SRCS))
OBJS=$(addprefix $(OBJS_DIR)/,$(RAW_OBJS))
OBJS_CLEAN=$(strip $(foreach f,$(OBJS),$(wildcard $(f))))
NAME_CLEAN=$(strip $(NAME))
LIBFT_A=$(LIBFT_DIR)/libft.a
INCLUDES:=-I includes -I $(LIBFT_DIR)/includes
FLAGS=-Wall -Wextra -Werror

RED=\033[0;31m
GREEN=\033[0;32m
BLUE=\033[0;34m
NC=\033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(OBJS_DIR):
	@echo "$(BLUE)Compiling $(NAME_CLEAN) objects files...$(NC)"
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	@gcc $(INCLUDES) $(FLAGS) -o $@ -c $<

$(LIBFT_A):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT_A) $(OBJS_DIR) $(OBJS)
	@echo "$(BLUE)Compiling executable...$(NC)"
	@gcc $(OBJS) $(LIBFT_A) $(INCLUDES) $(FLAGS) -o $(NAME)
	@echo "$(GREEN)Bin $(NAME) is ready to use!$(NC)"

clean:
ifneq ($(OBJS_CLEAN),)
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)$(NAME_CLEAN) objects files removed.$(NC)"
else
	@echo "$(RED)$(NAME_CLEAN) objects already cleaned$(NC)"
endif

fclean: clean
ifneq ($(NAME_CLEAN),)
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR)
	@rm -rf $(NAME)
	@echo "$(RED)Bin $(NAME_CLEAN) removed.$(NC)"
else
	@echo "$(RED)Objects and bin $(NAME_CLEAN) already cleaned$(NC)"
endif

test:
	gcc $(FLAGS) -g $(SRCS) -o $(NAME) $(INCLUDES) $(LIBFT_A)

re: fclean all
