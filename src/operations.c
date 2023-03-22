/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:58:37 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/22 10:03:12 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_push(t_stack *stack, int value, int where)
{
	stack->count++;
	if (where == HEAD)
	{
		stack->head = (stack->head + stack->size - 1) % stack->size;
		stack->values[stack->head] = value;
	}
	else if (where == TAIL)
	{
		stack->tail = (stack->tail + 1) % stack->size;
		stack->values[stack->tail] = value;
	}
}

static int	ft_pop(t_stack *stack, int where)
{
	int	result;

	result = -1;
	stack->count--;
	if (where == HEAD)
	{
		result = stack->values[stack->head];
		stack->head = (stack->head + 1) % stack->size;
	}
	else if (where == TAIL)
	{
		result = stack->values[stack->tail];
		stack->tail = (stack->tail + stack->size - 1) % stack->size;
	}
	return (result);
}

static void	ft_swap(t_stack *stack)
{
	int	temp;

	if (stack->count < 2)
		return ;
	temp = stack->values[stack->head];
	stack->values[stack->head] = stack->values[(stack->head + 1) % stack->size];
	stack->values[(stack->head + 1) % stack->size] = temp;
}

void	ft_execute_op(t_ps *data, char op)
{
	if (!!(op & SWAP) + !!(op & PUSH) + !!(op & ROT) + !!(op & REV) > 1
		|| ((op & (PUSH | A | B)) == (PUSH | A | B)))
		return ;
	if (op & SWAP && op & A)
		ft_swap(data->a);
	if (op & SWAP && op & B)
		ft_swap(data->b);
	if (op & PUSH && op & A && data->b->count > 0)
		ft_push(data->a, ft_pop(data->b, HEAD), HEAD);
	if (op & PUSH && op & B && data->a->count > 0)
		ft_push(data->b, ft_pop(data->a, HEAD), HEAD);
	if (op & ROT && op & A && data->a->count > 1)
		ft_push(data->a, ft_pop(data->a, HEAD), TAIL);
	if (op & ROT && op & B && data->b->count > 1)
		ft_push(data->b, ft_pop(data->b, HEAD), TAIL);
	if (op & REV && op & A && data->a->count > 1)
		ft_push(data->a, ft_pop(data->a, TAIL), HEAD);
	if (op & REV && op & B && data->b->count > 1)
		ft_push(data->b, ft_pop(data->b, TAIL), HEAD);
	ft_queue_op(data, op);
}
