/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:34:17 by arabenst          #+#    #+#             */
/*   Updated: 2023/04/03 21:13:25 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_three(t_ps *data, t_stack *stack)
{
	if (ft_is_in_order(stack))
		return ;
	if (*ft_peek(stack, 0) > *ft_peek(stack, 2)
		&& *ft_peek(stack, 0) > *ft_peek(stack, 1))
		ft_execute_op(data, ROT | stack->st);
	else if (*ft_peek(stack, 0) > *ft_peek(stack, 2)
		&& *ft_peek(stack, 0) < *ft_peek(stack, 1))
		ft_execute_op(data, REV | stack->st);
	else
		ft_execute_op(data, SWAP | stack->st);
	ft_sort_three(data, stack);
}

static int	ft_only_one_unsorted(t_stack *stack)
{
	int	i;
	int	j;
	int	n;
	int	only;

	if (stack->count != 5)
		return (-1);
	only = -1;
	i = -1;
	while (++i < stack->count)
	{
		n = ft_pop(stack, HEAD);
		j = -1;
		while (++j < stack->count)
		{
			if (ft_is_sorted(stack) && only == -1)
				only = n;
			ft_push(stack, ft_pop(stack, HEAD), TAIL);
		}
		ft_push(stack, n, HEAD);
		ft_push(stack, ft_pop(stack, HEAD), TAIL);
	}
	return (only);
}

static void	ft_sort_small(t_ps *data)
{
	int	only;

	only = ft_only_one_unsorted(data->a);
	if (only != -1)
	{
		ft_bring_to_top(data, A, only);
		ft_execute_op(data, PUSH | B);
		ft_bring_to_top(data, A, (only + 1) % data->a->size);
		ft_execute_op(data, PUSH | A);
		ft_bring_to_top(data, A, 0);
		return ;
	}
	while (data->a->count > 3)
		ft_execute_op(data, PUSH | B);
	ft_sort_three(data, data->a);
	while (data->b->count)
	{
		if (data->b->count > 1 && *ft_peek(data->b, 0) < *ft_peek(data->b, 1))
			ft_execute_op(data, SWAP | B);
		ft_bring_to_top(data, A, *ft_peek(data->b, 0) + 1);
		ft_execute_op(data, PUSH | A);
	}
	ft_bring_to_top(data, A, 0);
}

static void	ft_sort_radix_base2(t_ps *data)
{
	int	i;
	int	bit;

	bit = 0;
	while (!ft_is_sorted(data->a))
	{
		i = -1;
		while (++i < data->a->size)
		{
			if ((*ft_peek(data->a, 0) >> bit) & 1)
				ft_execute_op(data, ROT | A);
			else
				ft_execute_op(data, PUSH | B);
		}
		while (data->b->count)
			ft_execute_op(data, PUSH | A);
		bit++;
	}
}

void	ft_sort(t_ps *data)
{
	if (ft_is_sorted(data->a))
		ft_exit(data, 0);
	if (data->a->count == 2)
		ft_execute_op(data, SWAP | A);
	else if (data->a->count == 3)
		ft_sort_three(data, data->a);
	else if (data->a->count <= 5)
		ft_sort_small(data);
	else
		ft_sort_radix_base2(data);
}
