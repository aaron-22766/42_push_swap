/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:15:35 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/27 17:32:59 by arabenst         ###   ########.fr       */
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
# include <stdbool.h>
# include "../libft/libft.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

# define A 1
# define B 2
# define SWAP 4
# define PUSH 8
# define ROT 16
# define REV 32
# define CLEAR 64

# define HEAD 0
# define TAIL -1

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_stack
{
	int	*values;
	int	head;
	int	tail;
	int	count;
	int	size;
}	t_stack;

typedef struct s_ps
{
	t_stack	*a;
	t_stack	*b;
	char	*ops;
	char	**split;
}	t_ps;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// input.c
void	ft_get_input(t_ps *data, int argc, char **argv);

// stack.c
int		*ft_peek(t_stack *stack, int index);
void	ft_push(t_stack *stack, int value, int where);
int		ft_pop(t_stack *stack, int where);

// sort.c
void	ft_sort_three(t_ps *data, char st);
void	ft_sort(t_ps *data);

// sort_large.c
void	ft_sort_big(t_ps *data);
void	ft_sort_radix(t_ps *data);

// operations.c
void	ft_execute_op(t_ps *data, char op);

// optimize.c
void	ft_optimize_ops(t_ps *data, char *ops);

// ops_clean.c
void	ft_replace_manual_swap(char *ops, char st);
void	ft_too_many_rotations(t_ps *data, char *ops);

// utils.c
bool	ft_is_sorted(t_stack *stack);
void	ft_bring_to_top(t_ps *data, char st, int n);

// free.c
void	ft_free_split(t_ps *data);
void	ft_exit(t_ps *data, int error);

////////////////////////////////////////////////////////////////////////
void		print_stack(t_stack *stack);//REMOVE BEFORE EVAL (stack.c)//
void		ft_print_ops(char *ops);//////MAKE STATIC FUNC (push_swap.c)
////////////////////////////////////////////////////////////////////////

#endif