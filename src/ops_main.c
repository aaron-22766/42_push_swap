/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:48:32 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/06 12:48:53 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	from->count--;
	i = ++to->count;
	while (--i > to->top)
		to->stack[i] = to->stack[i - (!!i)];
	to->stack[to->top] = push;
}

void	ft_rotate(t_stack *stack, int reverse)
{
	if (stack->count < 2)
		return ;
	if (reverse)
		stack->top += -1 + !stack->top * stack->count;
	else
		stack->top = (stack->top + 1) % stack->count;
}
