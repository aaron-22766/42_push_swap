/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:34:17 by arabenst          #+#    #+#             */
/*   Updated: 2023/04/26 18:49:02 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_sort_three(t_ps *data, t_stack *stack)
{
	if (*ft_peek(stack, 0) < *ft_peek(stack, 1)
		&& *ft_peek(stack, 1) < *ft_peek(stack, 2))
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
}

void	ft_sort_large(t_ps *data)
{
	int	chunk_size;
	int	chunk;
	int	count;
	int	i;

	chunk_size = data->a->size / 2;
	chunk = 0;
	while (data->a->count)
	{
		count = data->a->count;
		i = -1;
		while (++i < count)
		{
			if (*ft_peek(data->a, 0) < (chunk + 1) * chunk_size)
			{
				ft_execute_op(data, PUSH | B);
				if (*ft_peek(data->b, 0) < chunk * chunk_size + chunk_size / 2)
					ft_execute_op(data, ROT | B);
			}
			else
				ft_execute_op(data, ROT | A);
		}
		chunk++;
	}
	ft_smart_insert(data);
}

void	ft_sort(t_ps *data)
{
	if (ft_is_sorted(data->a))
		ft_exit(data, false);
	if (data->a->count == 2)
		ft_execute_op(data, SWAP | A);
	else if (data->a->count == 3)
		ft_sort_three(data, data->a);
	else if (data->a->count <= 5)
		ft_sort_small(data);
	else
		ft_sort_large(data);
	ft_bring_to_top(data, A, 0);
}
