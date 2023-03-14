/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:58:37 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/14 16:58:42 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_execute_op(t_push_swap *data, char op)
{
	if (!!(op & SWAP) + !!(op & PUSH) + !!(op & ROT) + !!(op & REV) > 1
		|| ((op & (PUSH | A | B)) == (PUSH | A | B)))
		return ;
	if (op & SWAP && op & A)
		ft_swap(data->a);
	if (op & SWAP && op & B)
		ft_swap(data->b);
	if (op & PUSH && op & A)
		ft_push(data->b, data->a);
	if (op & PUSH && op & B)
		ft_push(data->a, data->b);
	if (op & ROT && op & A)
		ft_rotate(data->a);
	if (op & ROT && op & B)
		ft_rotate(data->b);
	if (op & REV && op & A)
		ft_reverse_rotate(data->a);
	if (op & REV && op & B)
		ft_reverse_rotate(data->b);
	ft_op_to_queue(data, op);
}

void	ft_swap(t_stack *stack)
{
	int	temp;

	if (stack->count < 2)
		return ;
	temp = stack->stack[stack->top];
	stack->stack[stack->top] = stack->stack[(stack->top + 1) % stack->count];
	stack->stack[(stack->top + 1) % stack->count] = temp;
}

void	ft_push(t_stack *from, t_stack *to)
{
	int	push;
	int	i;

	if (from->count < 1)
		return ;
	push = from->stack[from->top];
	i = from->top - 1;
	while (++i < from->count)
		from->stack[i] = from->stack[i + 1];
	if (--from->count)
		from->top = from->top % from->count;
	i = ++to->count;
	while (--i > to->top)
		to->stack[i] = to->stack[i - (!!i)];
	to->stack[to->top] = push;
}

void	ft_rotate(t_stack *stack)
{
	if (stack->count < 2)
		return ;
	stack->top = (stack->top + 1) % stack->count;
}

void	ft_reverse_rotate(t_stack *stack)
{
	if (stack->count < 2)
		return ;
	stack->top += -1 + !stack->top * stack->count;
}
