/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:25:59 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/27 13:26:24 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	ft_is_sorted(t_stack *stack)
{
	int	i;

	i = -1;
	while (++i + 1 < stack->count)
		if (*ft_peek(stack, i) > *ft_peek(stack, i + 1))
			return (false);
	return (true);
}
