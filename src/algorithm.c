/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:34:17 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/25 10:03:47 by arabenst         ###   ########.fr       */
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

static void	ft_sort_small(t_ps *data)
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

static void	ft_sort_radix(t_ps *data)
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
	if (ft_is_sorted(data->a))
		ft_exit(data, 0);
	if (data->a->count == 2)
		ft_execute_op(data, SWAP | A);
	else if (data->a->count == 3)
		ft_sort_three(data);
	else if (data->a->count <= 5)
		ft_sort_small(data);
	else if (data->a->count <= 500)
		ft_sort_big(data);
	else
		ft_sort_radix(data);
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
