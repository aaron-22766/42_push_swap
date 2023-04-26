/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:19:22 by arabenst          #+#    #+#             */
/*   Updated: 2023/04/26 19:35:05 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_get_distance(t_stack *stack, int num)
{
	int	i;

	if (num < 0)
		return (0);
	i = -1;
	while (ft_peek(stack, ++i))
		if (*ft_peek(stack, i) == num)
			break ;
	if (i > stack->count / 2)
		return (-1 * (stack->count - i));
	return (i);
}

static int	ft_next(t_stack *stack, int num)
{
	int	next;
	int	current;
	int	i;

	if (stack->count < 1)
		return (-1);
	next = INT32_MAX;
	i = -1;
	while (ft_peek(stack, ++i))
	{
		current = *ft_peek(stack, i);
		if (current > num && current < next)
			next = current;
	}
	if (next == INT32_MAX)
		return (ft_next(stack, -1));
	return (next);
}

static int	ft_calculate_moves(t_ps *data, int current)
{
	int	moves_a;
	int	moves_b;

	moves_a = ft_get_distance(data->a, ft_next(data->a, current));
	moves_b = ft_get_distance(data->b, current);
	if ((moves_a <= 0 && moves_b >= 0) || (moves_a >= 0 && moves_b <= 0))
		return (ft_abs(moves_a - moves_b));
	if (ft_abs(moves_a) > ft_abs(moves_b))
		return (ft_abs(moves_a));
	return (ft_abs(moves_b));
}

static int	ft_get_num_lowest(t_ps *data, int chunk_start, int chunk_size)
{
	int	chunk_end;
	int	num_lowest;
	int	lowest_moves;
	int	moves;

	chunk_end = chunk_start + chunk_size;
	lowest_moves = INT32_MAX;
	num_lowest = -1;
	while (chunk_start <= chunk_end)
	{
		moves = ft_calculate_moves(data, *ft_peek(data->b, chunk_start));
		if (moves < lowest_moves)
		{
			lowest_moves = moves;
			num_lowest = *ft_peek(data->b, chunk_start);
		}
		chunk_start++;
	}
	return (num_lowest);
}

void	ft_smart_insert(t_ps *data)
{
	int	num_lowest;
	int	chunk_size;
	int	chunk;
	int	chunk_start;

	chunk = -1;
	while (data->b->count)
	{
		chunk_size = data->b->size / 4;
		if (chunk_size > data->b->count)
			chunk_size = data->b->count;
		chunk_start = (++chunk % 2) * -chunk_size;
		while (chunk_size)
		{
			num_lowest = ft_get_num_lowest(data, chunk_start, --chunk_size);
			chunk_start -= ft_get_distance(data->b, num_lowest);
			if (chunk_start < -chunk_size
				|| chunk_start + chunk_size >= data->b->count)
				chunk_start = -chunk_size;
			ft_bring_to_top(data, A, ft_next(data->a, num_lowest));
			ft_bring_to_top(data, B, num_lowest);
			ft_execute_op(data, PUSH | A);
		}
	}
}
