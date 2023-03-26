/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:40:32 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/25 10:05:53 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_stack(t_stack *stack)
{
	int		i;
	int		count;
	char	*padding;

	count = 0;
	i = 0;
	while (i < stack->count)
		count += ft_printf("%d, ", *ft_peek(stack, i++));
	count = stack->size * 3 - count;
	padding = ft_calloc(count + 1, sizeof(char));
	if (!padding)
		return ;
	ft_memset(padding, ' ', count);
	ft_printf("%sh=%d t=%d c=%d s=%d\n", padding, stack->head,
		stack->tail, stack->count, stack->size);
	free(padding);
	// REMOVE BEFORE EVAL
}

int	*ft_peek(t_stack *st, int i)
{
	if (i >= 0 && i < st->count)
		return (&st->values[(st->head + i) % st->size]);
	else if (i < 0 && i >= -st->count)
		return (&st->values[(st->tail + i + st->size + 1) % st->size]);
	return (NULL);
}

void	ft_push(t_stack *stack, int value, int where)
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

int	ft_pop(t_stack *stack, int where)
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
