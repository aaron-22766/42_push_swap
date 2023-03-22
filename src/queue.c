/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:54:01 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/22 09:35:43 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_queue_op(t_ps *data, char op)
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

void	print_op(char op)
{
	if (op & SWAP)
		ft_printf("s%c\n", 'a' + !!(op & B) + 17 * !!(op & A && op & B));
	else if (op & PUSH)
		ft_printf("p%c\n", 'a' + !!(op & B));
	else if (op & ROT)
		ft_printf("r%c\n", 'a' + !!(op & B) + 16 * !!(op & A && op & B));
	else if (op & REV)
		ft_printf("rr%c\n", 'a' + !!(op & B) + 16 * !!(op & A && op & B));
}

void	ft_clean_swaps(char *ops, int i, int count[2])
{
	if (count[A - 1] % 2 && count[B - 1] % 2)
		ops[i] = SWAP | A | B;
	else if (count[A - 1] % 2)
		ops[i] = SWAP | A;
	else if (count[B - 1] % 2)
		ops[i] = SWAP | B;
}

void	ft_clean_rotate(char *ops, int action, int i, int count[2])
{
	int	j;

	j = i;
	while (j - i < (count[A - 1] * (count[A - 1] <= count[B - 1])
			+ count[B - 1] * (count[B - 1] < count[A - 1])))
		ops[j++] = action | A | B;
	while (j - i < count[A - 1])
		ops[j++] = action | A;
	while (j - i < count[B - 1])
		ops[j++] = action | B;
}

void	ft_clean_multiples(char *ops, char action, int i)
{
	int	j;
	int	count[2];

	count[A - 1] = 0;
	count[B - 1] = 0;
	j = i - 1;
	while (ops[++j] & action)
	{
		if ((ops[j] ^ action) & A)
			count[A - 1]++;
		if ((ops[j] ^ action) & B)
			count[B - 1]++;
		ops[j] = ops[j] ^ action;
	}
	if (action & SWAP)
		ft_clean_swaps(ops, i, count);
	else if ((action & ROT) || (action & REV))
		ft_clean_rotate(ops, action, i, count);
}

void	ft_clean_mixed(char *ops, int i)
{
	// pb
	// pb
	// sa
	// ra
	// sb
	// rra
	// pa
	// pa
	// rra
	// rra
	(void)ops;
	(void)i;
}

void	ft_optimize_ops(t_ps *data)
{
	int	i;

	i = -1;
	while (data->ops[++i])
	{
		ft_clean_multiples(data->ops, SWAP, i);
		ft_clean_multiples(data->ops, ROT, i);
		ft_clean_multiples(data->ops, REV, i);
		ft_clean_mixed(data->ops, i);
	}
}

void	ft_print_ops(t_ps *data)
{
	int		i;
	char	op;

	i = -1;
	while (data->ops[++i])
	{
		op = data->ops[i];
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
