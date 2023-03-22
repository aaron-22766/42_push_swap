/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:34:17 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/22 16:53:02 by arabenst         ###   ########.fr       */
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

int	ft_is_sorted(t_stack *stack)
{
	int	i;

	i = -1;
	while (++i + 1 < stack->count)
		if (*ft_peek(stack, i) > *ft_peek(stack, i + 1))
			return (0);
	return (1);
}

void	ft_sort_three(t_ps *data)
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

void	ft_bring_to_top(t_ps *data, int n)
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

void	ft_sort_medium(t_ps *data)
{
	while (data->a->count > 3)
		ft_execute_op(data, PUSH | B);
	ft_sort_three(data);
	while (data->b->count)
	{
		if (data->b->count > 1 && *ft_peek(data->b, 0) < *ft_peek(data->b, 1))
			ft_execute_op(data, SWAP | B);
		if (*ft_peek(data->a, 0) != *ft_peek(data->b, 0) + 1
			&& *ft_peek(data->b, 0) != data->a->size - 1)
			ft_bring_to_top(data, *ft_peek(data->b, 0) + 1);
		ft_execute_op(data, PUSH | A);
	}
	ft_bring_to_top(data, 0);
}

void	ft_radix_sort(t_ps *data)
{
	int	count;
	int	i;
	int	bit;

	count = data->a->count;
	bit = 0;
	while (!ft_is_sorted(data->a))
	{
		i = -1;
		while (++i < count)
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
	if (data->a->count == 2)
		ft_execute_op(data, SWAP | A);
	else if (data->a->count == 3)
		ft_sort_three(data);
	else if (data->a->count <= 5)
		ft_sort_medium(data);
	else
		ft_radix_sort(data);
}

/**
 * better algo!!
 * 
 * 4 1 2 3 0:
 * pb
 * rra
 * pa
 * ra
 * 
 */
