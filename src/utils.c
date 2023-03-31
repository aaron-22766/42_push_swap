/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:25:59 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/29 16:55:29 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	ft_is_sorted(t_stack *stack)
{
	int	i;

	i = 0;
	while (ft_peek(stack, ++i))
		if (*ft_peek(stack, i - 1) + (stack->st == A) * 2 - 1
			!= *ft_peek(stack, i))
			return (false);
	return (true);
}

bool	ft_is_in_order(t_stack *stack)
{
	int	i;

	i = -stack->st + 1;
	while (ft_peek(stack, i + (stack->st == A) * 2 - 1))
	{
		if (*ft_peek(stack, i) > *ft_peek(stack, i + (stack->st == A) * 2 - 1))
			return (false);
		i += (stack->st == A) * 2 - 1;
	}
	return (true);
}

void	ft_bring_to_top(t_ps *data, char st, int n)
{
	t_stack	*stack;
	int		i;

	stack = data->a;
	if (st == B)
		stack = data->b;
	i = -1;
	while (++i < stack->count)
		if (*ft_peek(stack, i) == n)
			break ;
	if (i > stack->count / 2)
		while (i++ < stack->count)
			ft_execute_op(data, REV | stack->st);
	else
		while (i-- > 0)
			ft_execute_op(data, ROT | stack->st);
}
