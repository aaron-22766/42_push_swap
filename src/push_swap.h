/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:15:35 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/16 17:37:29 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "../lib/libft/libft.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

# define A 1
# define B 2
# define SWAP 4
# define PUSH 8
# define ROT 16
# define REV 32

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_stack
{
	int	*stack;
	int	count;
	int	top;
}	t_stack;

typedef struct s_push_swap
{
	t_stack	*a;
	t_stack	*b;
	char	*queue;
	size_t	q_size;
	char	**split;
}	t_push_swap;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// input.c
t_push_swap	*ft_init_data(void);
void		ft_get_input(t_push_swap *data, int argc, char **argv);

// algorithm.c
int			ft_is_sorted(t_stack *stack);
void		ft_sort_into_queue(t_push_swap *data);

// queue.c
void		ft_op_to_queue(t_push_swap *data, char op);
void		ft_optimize_queue(char *queue);
void		ft_print_queue(t_push_swap *data);

// operations.c
void		ft_execute_op(t_push_swap *data, char op);
void		ft_swap(t_stack *stack);
void		ft_push(t_stack *from, t_stack *to);
void		ft_rotate(t_stack *stack);
void		ft_reverse_rotate(t_stack *stack);

// free.c
void		ft_free_split(t_push_swap *data);
void		ft_free_data(t_push_swap *data);
void		ft_exit(t_push_swap *data, int error);

#endif