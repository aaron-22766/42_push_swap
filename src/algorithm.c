/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:34:17 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/17 14:49:26 by arabenst         ###   ########.fr       */
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
	int	first;
	int	second;
	int	third;

	first = data->a->stack[data->a->top];
	second = data->a->stack[(data->a->top + 1) % data->a->count];
	third = data->a->stack[(data->a->top + 2) % data->a->count];
	if (first > third && first > second)
		ft_execute_op(data, ROT | A);
	else if (first > third && first < second)
		ft_execute_op(data, REV | A);
	else
		ft_execute_op(data, SWAP | A);
	if (!ft_is_sorted(data->a))
		ft_sort_three(data);
}

void	ft_bring_to_top(t_push_swap *data, int n)
{
	int	i;

	i = -1;
	while (++i < data->a->count)
		if (data->a->stack[(data->a->top + i) % data->a->count] == n)
			break ;
	if (i > data->a->count / 2)
		while (i++ < data->a->count)
			ft_execute_op(data, REV | A);
	else
		while (i-- > 0)
			ft_execute_op(data, ROT | A);
}

void	ft_sort_medium(t_push_swap *data)
{
	while (data->a->count > 3)
		ft_execute_op(data, PUSH | B);
	ft_sort_three(data);
	while (data->b->count)
	{
		if (data->b->stack[data->b->top] < data->b->stack[(data->b->top + 1)
				% data->b->count])
			ft_execute_op(data, SWAP | B);
		if (data->a->stack[data->a->top] != data->b->stack[data->b->top] + 1
			&& data->b->stack[data->b->top]
			!= data->a->count + data->b->count - 1)
			ft_bring_to_top(data, data->b->stack[data->b->top] + 1);
		ft_execute_op(data, PUSH | A);
	}
	ft_bring_to_top(data, 0);
}

int	ft_count_upcoming(t_push_swap *data, int size, int bit, int i)
{
	int	count;

	count = 0;
	while (i < size)
	{
		if ((data->a->stack[(data->a->top + i) % data->a->count] >> bit) & 1)
			count++;
		i++;
	}
	return (count);
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
		while (++i < size && ft_count_upcoming(data, size, bit, i))
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
	else if (data->a->count <= 5)
		ft_sort_medium(data);
	else
		ft_radix_sort(data);
}
