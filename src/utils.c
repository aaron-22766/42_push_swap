/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:25:59 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/25 09:29:53 by arabenst         ###   ########.fr       */
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
