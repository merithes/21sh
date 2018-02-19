# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/17 14:50:04 by vboivin           #+#    #+#              #
#    Updated: 2018/02/12 15:43:49 by jamerlin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= 21sh
HPATH		= includes
INC			= -I$(HPATH) -Ilibft/includes
FLAGS		= -Wall -Werror -Wextra #-fsanitize=address -g3 -fbounds-check
COMP		= gcc
LIBFT		= -Llibft -lft -lcurses

SRCS 		=	main.c env.c init_env.c manage_env.c prompt.c command.c		\
				bin_nenv.c bin_env.c edit_var.c interpret_env_cli.c			\
				error_handler.c free_list.c splitter.c terminit.c get_line.c \
				ft_error.c k_arrows_sides.c k_del.c k_home_end.c \
				k_arrows_histo.c k_arrows_skipwd.c move_cursor.c exec_cli_lst.c\
				cut_string_lst.c exec_lst.c clear_scrn.c splitter_alt.c \
				set_link.c free_rec_listc.c detect_delimiters.c \
				detect_delimiters_listing-stuff.c lexer.c redir.c \
				check_redirs.c analyze_spleet.c bad_redirs.c \
				format_redirections.c
DIR_SRC		= $(addprefix $(SRCPATH)/, $(SRCS))
SRCPATH		= src

OBJ 		= $(SRCS:.c=.o)
DIR_OBJ		= $(addprefix $(OBJPATH)/, $(OBJ))
OBJPATH		= obj

all: $(NAME)

$(OBJPATH)/%.o: $(SRCPATH)/%.c
	@printf "Compiling $<                                             \r"
	@$(COMP) $(FLAGS) -c $< -o $@ $(INC)

$(NAME): $(DIR_OBJ)
	@printf "                                                         \r"
	@printf "main compilation:\tdone\n"
	@make -C libft
	@echo "vboivin" > auteur
	@$(COMP) $(DIR_OBJ) -o $(NAME) $(INCMAC) $(LIBFT) $(FLAGS) 

clean:
	@make clean -C libft
	@rm -rf $(DIR_OBJ)

fclean: rmtest
	@make fclean -C libft
	@rm -rf $(DIR_OBJ)
	@rm -rf $(NAME)
test:
	@mkdir test_dir
	@mkdir test_dir/test_rec
	@mkdir test_dir/test_rec2
	@touch test_dir/test_file
	@touch test_dir/test_file2
	@chmod 7000 test_dir/test_file
	@chmod 7777 test_dir/test_file2
	@ln -s test_dir/test_file test_dir/test_link

rmtest:
	@rm -rf test_dir

re: fclean all
