/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:58:37 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/22 16:56:33 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_swap(t_stack *stack)
{
	int	temp;

	if (stack->count < 2)
		return ;
	temp = *ft_peek(stack, 0);
	*(ft_peek(stack, 0)) = *ft_peek(stack, 1);
	*ft_peek(stack, 1) = temp;
}

static void	ft_queue_op(t_ps *data, char op)
{
	static size_t	size;
	static size_t	i;
	char			*temp;

	if (i == size)
	{
		if (!size)
			size = 1;
		else if (size < 1024)
			size *= 2;
		else
			size += 1024;
		temp = ft_calloc(size + 1, sizeof(char));
		if (!temp)
			ft_exit(data, 1);
		if (data->ops)
			ft_strlcpy(temp, data->ops, size + 1);
		free(data->ops);
		data->ops = temp;
	}
	data->ops[i++] = op;
}

void	ft_execute_op(t_ps *data, char op)
{
	if (!!(op & SWAP) + !!(op & PUSH) + !!(op & ROT) + !!(op & REV) > 1
		|| ((op & (PUSH | A | B)) == (PUSH | A | B)))
		return ;
	if (op & SWAP && op & A)
		ft_swap(data->a);
	if (op & SWAP && op & B)
		ft_swap(data->b);
	if (op & PUSH && op & A && data->b->count > 0)
		ft_push(data->a, ft_pop(data->b, HEAD), HEAD);
	if (op & PUSH && op & B && data->a->count > 0)
		ft_push(data->b, ft_pop(data->a, HEAD), HEAD);
	if (op & ROT && op & A && data->a->count > 1)
		ft_push(data->a, ft_pop(data->a, HEAD), TAIL);
	if (op & ROT && op & B && data->b->count > 1)
		ft_push(data->b, ft_pop(data->b, HEAD), TAIL);
	if (op & REV && op & A && data->a->count > 1)
		ft_push(data->a, ft_pop(data->a, TAIL), HEAD);
	if (op & REV && op & B && data->b->count > 1)
		ft_push(data->b, ft_pop(data->b, TAIL), HEAD);
	ft_queue_op(data, op);
}
