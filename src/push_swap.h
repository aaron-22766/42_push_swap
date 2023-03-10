/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:15:35 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/10 10:59:28 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include "../lib/libft/src/libft.h"

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
void		ft_sort(t_push_swap *data);

// ops_main.c
void		ft_swap(t_stack *stack);
void		ft_push(t_stack *from, t_stack *to);
void		ft_rotate(t_stack *stack, int reverse);

// ops_ps.c
void		ft_sa(t_push_swap *data);
void		ft_sb(t_push_swap *data);
void		ft_ss(t_push_swap *data);
void		ft_pa(t_push_swap *data);
void		ft_pb(t_push_swap *data);

// ops_rot.c
void		ft_ra(t_push_swap *data);
void		ft_rb(t_push_swap *data);
void		ft_rr(t_push_swap *data);

// ops_revrot.c
void		ft_rra(t_push_swap *data);
void		ft_rrb(t_push_swap *data);
void		ft_rrr(t_push_swap *data);

// free.c
void		ft_free_split(t_push_swap *data);
void		ft_free_data(t_push_swap *data);
void		ft_exit(t_push_swap *data, int error);

#endif