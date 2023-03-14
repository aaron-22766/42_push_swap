/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:54:01 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/14 16:56:01 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_op_to_queue(t_push_swap *data, char op)
{
	static size_t	i;
	char			*temp;

	if (i == data->q_size)
	{
		data->q_size *= 2;
		temp = ft_calloc(data->q_size + 1, sizeof(char));
		if (!temp)
			ft_exit(data, 1);
		ft_strlcpy(temp, data->queue, data->q_size + 1);
		free(data->queue);
		data->queue = temp;
	}
	data->queue[i++] = op;
}

void	ft_optimize_queue(char *queue)
{
	(void)queue;
	return ;
}

void	ft_print_queue(t_push_swap *data)
{
	int		i;
	char	op;

	i = -1;
	while (data->queue[++i])
	{
		op = data->queue[i];
		if (op & SWAP)
			ft_printf("s%c\n", 'a' + !!(op & B) + 17 * !!(op & A && op & B));
		else if (op & PUSH)
			ft_printf("p%c\n", 'a' + !!(op & B));
		else if (op & ROT)
			ft_printf("r%c\n", 'a' + !!(op & B) + 16 * !!(op & A && op & B));
		else if (op & REV)
			ft_printf("rr%c\n", 'a' + !!(op & B) + 16 * !!(op & A && op & B));
	}
}
