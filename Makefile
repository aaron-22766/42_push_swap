# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/14 17:40:26 by arabenst          #+#    #+#              #
#    Updated: 2023/03/08 13:50:40 by arabenst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	push_swap

SRCDIR		=	./src
OBJDIR		=	./obj
LIBDIR		=	./lib
TESTDIR		=	./tests
TESTOBJDIR	=	$(TESTDIR)/obj
TEST		=	$(TESTDIR)/test

SRCS		=	$(wildcard $(SRCDIR)/*.c)
OBJS		=	$(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))
TESTSRCS	=	$(wildcard $(TESTDIR)/*.c)
TESTOBJS	=	$(addprefix $(TESTOBJDIR)/,$(notdir $(TESTSRCS:.c=.o)))
PROJOBJS	=	$(filter-out ./obj/push_swap.o, $(OBJS))

# **************************************************************************** #
#                               CHANGE WILDCARD                                #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

RM			=	rm
RMFLAGS		=	-rf

LIBFT_DIR	=	$(LIBDIR)/libft
LIBFT_LIB	=	libft.a
LIBFT		=	$(LIBFT_DIR)/$(LIBFT_LIB)

ARCS		=	$(LIBFT)

CHECK_LIB	=	-lcheck -L $(HOME)/.brew/opt/check/lib/
CHECK_INC	=	-I $(HOME)/.brew/opt/check/include/

$(NAME): $(LIBFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(ARCS)

$(LIBFT): $(LIBDIR)
	git clone https://github.com/aaron-22766/libft.git $(LIBFT_DIR); make -C $(LIBFT_DIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TESTOBJDIR)/%.o: $(TESTDIR)/%.c | $(TESTOBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@ $(CHECK_INC)

$(TESTOBJDIR):
	mkdir -p $(TESTOBJDIR)

$(TEST): $(TESTOBJS) $(PROJOBJS) $(ARCS)
	$(CC) -o $(TEST) $(TESTOBJS) $(PROJOBJS) $(ARCS) $(CHECK_LIB) $(CHECK_INC)

all: $(NAME)

clean: test_clean
	$(RM) $(RMFLAGS) $(OBJDIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)
	make -C $(LIBFT_DIR) fclean

libclean: fclean
	$(RM) $(RMFLAGS) $(LIBDIR)

re: fclean all

reb: fclean bonus

test: $(TEST)
	./$(TEST)

test_clean:
	$(RM) $(RMFLAGS) $(TESTOBJDIR) $(TEST)

test_re: test_clean test

.PHONY: all clean fclean libclean re reb