/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_quick.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:32:02 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/30 16:42:58 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#define DEBUG 0

static t_stack	**ft_init_chunks(t_ps *data)
{
	t_stack	**chunks;
	int		i;

	chunks = ft_calloc(ft_log2_int(data->a->size) + 1, sizeof(t_stack *));
	if (!chunks)
		ft_exit(data, 1);
	i = -1;
	while (++i < ft_log2_int(data->a->size) + 1)
	{
		chunks[i] = ft_init_stack(data, A);
		chunks[i]->values = malloc(sizeof(int) * data->a->size / ft_pow(2, i));
		if (!chunks[i]->values)
			ft_exit(data, 1);
	}
	return (chunks);
}

static void	ft_copy_chunk(t_stack *to, t_stack *from)
{
	to->st = from->st;
	to->head = from->head;
	to->tail = from->tail;
	to->count = from->count;
	to->size = from->size;
	ft_memcpy(to->values, from->values, from->size * sizeof(int));
}

static int	ft_smallest_num(t_stack *stack)
{
	int	smallest;
	int	i;

	smallest = INT32_MAX;
	i = -1;
	while (ft_peek(stack, ++i))
		if (*ft_peek(stack, i) < smallest)
			smallest = *ft_peek(stack, i);
	return (smallest);
}

static int	ft_largest_num(t_stack *stack)
{
	int	largest;
	int	i;

	largest = -1;
	i = -1;
	while (ft_peek(stack, ++i))
		if (*ft_peek(stack, i) > largest)
			largest = *ft_peek(stack, i);
	return (largest);
}

static int	ft_cheaper_num(t_stack *stack, int pivot)
{
	int	top;
	int	bottom;

	top = 0;
	if (stack->st == A)
		while (*ft_peek(stack, top) >= pivot)
			top++;
	else
		while (*ft_peek(stack, top) <= pivot)
			top++;
	bottom = -1;
	if (stack->st == A)
		while (*ft_peek(stack, bottom) >= pivot)
			bottom--;
	else
		while (*ft_peek(stack, bottom) <= pivot)
			bottom--;
	if (ft_abs(bottom) < top)
		return (*ft_peek(stack, bottom));
	return (*ft_peek(stack, top));
}

static void	ft_bring_to_top_in_chunk(t_stack *chunk, int n)
{
	int	i;

	i = -1;
	while (++i < chunk->count)
		if (*ft_peek(chunk, i) == n)
			break ;
	if (i > chunk->count / 2)
		while (i++ < chunk->count)
			ft_push(chunk, ft_pop(chunk, TAIL), HEAD);
	else
		while (i-- > 0)
			ft_push(chunk, ft_pop(chunk, HEAD), TAIL);
}

static int	ft_new_chunk_index(t_ps *data)
{
	int	i;

	i = 1;
	while (data->chunks[i]->count)
		i++;
	return (i);
}

static void	ft_empty_chunk(t_ps *data, int i)
{
	t_stack	*chunk;
	int		new;

	chunk = data->chunks[i];
	if (DEBUG)
		ft_printf("Emptying...\n");
	if (DEBUG)
		ft_print_stack(chunk);
	if (chunk->count == 2 && !ft_is_in_order(chunk))
	{
		ft_execute_op(data, SWAP | chunk->st);
		ft_push(chunk, ft_pop(chunk, HEAD), TAIL);
	}
	if (i == 0 || (chunk->st == A && chunk->count <= 2
			&& ft_is_sorted(data->a)))
	{
		while (chunk->count)
			ft_pop(chunk, HEAD);
		if (DEBUG)
			ft_printf("Cleared\n");
		return ;
	}
	if (chunk->count <= 2 && ((chunk->st == B && ft_is_sorted(data->a))
			|| (chunk->st == A && ft_is_sorted(data->b))))
	{
		while (chunk->count)
		{
			ft_bring_to_top(data, chunk->st, *ft_peek(chunk, 0));
			ft_execute_op(data, PUSH | (A + B - chunk->st));
			ft_pop(chunk, HEAD);
			if (DEBUG)
				ft_printf("Moved and Cleared\n");
		}
	}
	new = ft_new_chunk_index(data);
	if (DEBUG)
		ft_printf("to new: %d\n", new);
	while (chunk->count)
	{
		ft_bring_to_top(data, chunk->st, *ft_peek(chunk, 0));
		ft_execute_op(data, PUSH | (A + B - chunk->st));
		ft_push(data->chunks[new], ft_pop(chunk, HEAD), HEAD);
		if (DEBUG)
			ft_printf("Returned to new: %d\n", new);
	}
	if (DEBUG)
	{
		ft_printf("******************\n");
		if (chunk->st == A)
			ft_print_stack(data->b);
		else
			ft_print_stack(data->a);
		ft_printf("******************\n");
	}
}

static void	ft_pivot(t_ps *data, t_stack *chunk, t_stack *stack, int last)
{
	int	pivot;
	int	rest;

	pivot = (ft_smallest_num(chunk) + ft_largest_num(chunk) + 1) / 2
		- (chunk->st == B && !(chunk->count % 2) && chunk->count > 3);
	rest = (chunk->count + 1) / 2;
	if (DEBUG)
		ft_printf("pivot: %d, rest: %d\n", pivot, rest);
	data->chunks[last]->size = chunk->count - rest;
	data->chunks[last]->st = A + B - chunk->st;
	while (chunk->count > rest)
	{
		if (DEBUG)
			ft_printf("cheaper: %d\n", ft_cheaper_num(stack, pivot));
		ft_bring_to_top_in_chunk(chunk, ft_cheaper_num(stack, pivot));
		ft_push(data->chunks[last], ft_pop(chunk, HEAD), HEAD);
		ft_bring_to_top(data, chunk->st, ft_cheaper_num(stack, pivot));
		ft_execute_op(data, PUSH | (A + B - chunk->st));
		if (DEBUG)
			ft_print_stack(chunk);
	}
	if (DEBUG)
		ft_print_stack(data->chunks[last]);
}

static void	ft_bisect_chunk(t_ps *data, int i, int last)
{
	t_stack	*chunk;
	t_stack	*stack;

	if (DEBUG)
		ft_printf("------------------\n");
	if (data->a->count == data->a->size && ft_is_sorted(data->a))
		return ;
	chunk = data->chunks[i];
	stack = data->a;
	if (chunk->st == B)
		stack = data->b;
	if (chunk->count <= 2 || ft_is_sorted(chunk))
	{
		ft_empty_chunk(data, i);
		return ;
	}
	if (DEBUG)
	{
		ft_print_stack(chunk);
		ft_printf("i: %d last: %d\n", i, last);
	}
	ft_pivot(data, chunk, stack, last);
	ft_bisect_chunk(data, i, last + 1);
	ft_bisect_chunk(data, last, last + 1);
}

void	ft_sort_quick(t_ps *data)
{
	data->chunks = ft_init_chunks(data);
	ft_copy_chunk(data->chunks[0], data->a);
	ft_bisect_chunk(data, 0, 1);
	while (data->b->count)
		ft_execute_op(data, PUSH | A);
	// ft_bring_to_top(data, A, 0);
	if (DEBUG)
		ft_printf("==================\n");
	if (DEBUG)
		ft_print_stack(data->a);
}
