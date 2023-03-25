/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:32:02 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/25 10:18:46 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_big(t_ps *data)
{
	(void)data;
}

void	ft_sort_radix(t_ps *data)
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
