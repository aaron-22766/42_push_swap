/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:40:32 by arabenst          #+#    #+#             */
/*   Updated: 2023/04/22 15:16:38 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*ft_init_stack(t_ps *data, char st)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		ft_exit(data, true);
	stack->st = st;
	stack->values = NULL;
	stack->head = HEAD;
	stack->tail = TAIL;
	stack->count = 0;
	stack->size = 0;
	return (stack);
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
	int	*result;

	result = ft_peek(stack, where);
	if (!result)
		return (-1);
	stack->count--;
	if (where == HEAD)
		stack->head = (stack->head + 1) % stack->size;
	else if (where == TAIL)
		stack->tail = (stack->tail + stack->size - 1) % stack->size;
	return (*result);
}

// only for debugging purposes
void	ft_print_stack(t_stack *stack)
{
	int	i;

	i = -1;
	while (++i < stack->size)
	{
		if (ft_peek(stack, i))
			ft_printf("%d, ", *ft_peek(stack, i));
		else
			ft_printf("-, ");
	}
	ft_printf("\n|%c| h=%d, t=%d, c=%d, s=%d\n", 'A' + stack->st - 1,
		stack->head, stack->tail, stack->count, stack->size);
}
