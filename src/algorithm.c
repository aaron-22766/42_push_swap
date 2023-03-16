/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:34:17 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/16 17:09:00 by arabenst         ###   ########.fr       */
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

void	ft_sort_three(t_push_swap *data)
{
	if (data->a->stack[data->a->top] == 2)
		ft_execute_op(data, ROT | A);
	else if (data->a->stack[data->a->top] == 1
		&& data->a->stack[(data->a->top + 1) % data->a->count] == 2)
		ft_execute_op(data, REV | A);
	else
		ft_execute_op(data, SWAP | A);
	if (!ft_is_sorted(data->a))
		ft_sort_three(data);
}

int	ft_get_index_of_lowest_number(t_stack *stack)
{
	int	i;
	int	lowest;
	int	index;

	lowest = INT_MAX;
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

void	ft_selection_sort(t_push_swap *data)
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

void	ft_radix_sort(t_push_swap *data)
{
	int	size;
	int	i;
	int	bit;

	size = data->a->count;
	bit = 0;
	while (!(ft_is_sorted(data->a)))
	{
		i = -1;
		while (++i < size)
		{
			if ((data->a->stack[data->a->top] >> bit) & 1)
				ft_execute_op(data, ROT | A);
			else
				ft_execute_op(data, PUSH | B);
		}
		while (data->b->count)
			ft_execute_op(data, PUSH | A);
		bit++;
	}
}

void	ft_sort_into_queue(t_push_swap *data)
{
	if (data->a->count == 2)
		ft_execute_op(data, SWAP | A);
	else if (data->a->count == 3)
		ft_sort_three(data);
	else if (data->a->count < 10)
		ft_selection_sort(data);
	else
		ft_radix_sort(data);
	// print_stack(data->a);
}
