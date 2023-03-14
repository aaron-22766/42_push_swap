/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:34:17 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/14 16:35:33 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_stack(t_stack *stack)
{
	int	i;

	i = -1;
	while (++i < stack->count)
	{
		if (i)
			ft_printf(", ");
		ft_printf("%d", stack->stack[(stack->top + i) % stack->count]);
	}
	ft_printf("\t| top=%d | count=%d\n", stack->top, stack->count);
	// REMOVE BEFORE EVAL
}

int	ft_is_sorted(t_stack *stack)
{
	int	i;

	i = -1;
	while (++i + 1 < stack->count)
		if (stack->stack[stack->top + i]
			> stack->stack[(stack->top + i + 1) % stack->count])
			return (0);
	return (1);
}

int	ft_get_index_of_lowest_number(t_stack *stack)
{
	int	i;
	int	lowest;
	int	index;

	lowest = INT32_MAX;
	i = -1;
	while (++i < stack->count)
	{
		if (stack->stack[(stack->top + i) % stack->count] < lowest)
		{
			lowest = stack->stack[(stack->top + i) % stack->count];
			index = i;
		}
	}
	return (index);
}

void	ft_sort_into_queue(t_push_swap *data)
{
	int	i;

	while (data->a->count)
	{
		i = ft_get_index_of_lowest_number(data->a);
		if (i <= data->a->count / 2)
			while (--i >= 0)
				ft_execute_op(data, ROT | A);
		else
			while (data->a->count - ++i >= 0)
				ft_execute_op(data, REV | A);
		ft_execute_op(data, PUSH | B);
	}
	while (data->b->count)
		ft_execute_op(data, PUSH | A);
}
