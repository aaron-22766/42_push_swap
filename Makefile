# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/14 17:40:26 by arabenst          #+#    #+#              #
#    Updated: 2023/04/26 11:56:38 by arabenst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	push_swap

SRCDIR		=	./src
OBJDIR		=	./obj

SRCS		=	$(wildcard $(SRCDIR)/*.c)
OBJS		=	$(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

# **************************************************************************** #
#                               CHANGE WILDCARD                                #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

RM			=	rm
RMFLAGS		=	-rf

LIBFT_DIR	=	./libft
LIBFT_LIB	=	libft.a
LIBFT		=	$(LIBFT_DIR)/$(LIBFT_LIB)

ARCS		=	$(LIBFT)

CHECK_LIB	=	-lcheck -L $(HOME)/.brew/opt/check/lib/
CHECK_INC	=	-I $(HOME)/.brew/opt/check/include/

VIS_DIR		=	./visualizer
VIS_EXE		=	$(VIS_DIR)/build/bin/visualizer

TESTER		=	./ps_tester.pl

$(NAME): $(LIBFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(ARCS)

$(LIBFT):
	git clone https://github.com/aaron-22766/libft.git $(LIBFT_DIR); make -C $(LIBFT_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(VIS_DIR):
	git clone https://github.com/o-reo/push_swap_visualizer.git $(VIS_DIR); (cd $(VIS_DIR) && mkdir build)

$(VIS_EXE): $(VIS_DIR)
	(cd $(VIS_DIR)/build && cmake .. && make)

all: $(NAME)

clean:
	$(RM) $(RMFLAGS) $(OBJDIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)
	make -C $(LIBFT_DIR) fclean

libclean:
	$(RM) $(RMFLAGS) $(LIBFT_DIR)

allclean: libclean visclean fclean
	$(RM) $(RMFLAGS) $(VIS_DIR) $(TESTER) .push_swap_test_results.log imgui.ini

re: fclean all

reb: fclean bonus

vis: $(NAME) $(VIS_EXE)
	$(VIS_EXE)

visclean:
	$(RM) $(RMFLAGS) $(VIS_DIR)

$(TESTER):
	curl https://raw.githubusercontent.com/lorenuars19/push_swap_tester/main/push_swap_tester.pl -o $(TESTER)

3: $(NAME) $(TESTER)
	perl $(TESTER) 3 100

5: $(NAME) $(TESTER)
	perl $(TESTER) 5 100

100: $(NAME) $(TESTER)
	perl $(TESTER) 100 1000

500: $(NAME) $(TESTER)
	perl $(TESTER) 500 100

.PHONY: all clean fclean libclean allclean re reb vis visclean 3 5 100 500
