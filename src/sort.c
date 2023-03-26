/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:34:17 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/25 17:46:21 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_sort_three(t_ps *data)
{
	if (ft_is_sorted(data->a))
		return ;
	if (*ft_peek(data->a, 0) > *ft_peek(data->a, 2)
		&& *ft_peek(data->a, 0) > *ft_peek(data->a, 1))
		ft_execute_op(data, ROT | A);
	else if (*ft_peek(data->a, 0) > *ft_peek(data->a, 2)
		&& *ft_peek(data->a, 0) < *ft_peek(data->a, 1))
		ft_execute_op(data, REV | A);
	else
		ft_execute_op(data, SWAP | A);
	ft_sort_three(data);
}

static void	ft_bring_to_top(t_ps *data, int n)
{
	int	i;

	i = -1;
	while (++i < data->a->count)
		if (*ft_peek(data->a, i) == n)
			break ;
	if (i > data->a->count / 2)
		while (i++ < data->a->count)
			ft_execute_op(data, REV | A);
	else
		while (i-- > 0)
			ft_execute_op(data, ROT | A);
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
		ft_bring_to_top(data, only);
		ft_execute_op(data, PUSH | B);
		ft_bring_to_top(data, (only + 1) % data->a->size);
		ft_execute_op(data, PUSH | A);
		ft_bring_to_top(data, 0);
		return ;
	}
	while (data->a->count > 3)
		ft_execute_op(data, PUSH | B);
	ft_sort_three(data);
	while (data->b->count)
	{
		if (data->b->count > 1 && *ft_peek(data->b, 0) < *ft_peek(data->b, 1))
			ft_execute_op(data, ROT | B);
		if (*ft_peek(data->a, 0) != *ft_peek(data->b, 0) + 1
			&& *ft_peek(data->b, 0) != data->a->size - 1)
			ft_bring_to_top(data, *ft_peek(data->b, 0) + 1);
		ft_execute_op(data, PUSH | A);
	}
	ft_bring_to_top(data, 0);
}

void	ft_sort(t_ps *data)
{
	if (ft_is_sorted(data->a))
		ft_exit(data, 0);
	if (data->a->count == 2)
		ft_execute_op(data, SWAP | A);
	else if (data->a->count == 3)
		ft_sort_three(data);
	else if (data->a->count <= 5)
		ft_sort_small(data);
	else if (data->a->count <= 500)
		ft_sort_radix(data);
	else
		ft_sort_radix(data);
}
