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

static void	ft_clean_push(char *ops, int count_a, int count_b)
{
	int	i;

	i = count_a;
	if (count_a > count_b)
		i = count_b;
	while (i < count_a)
		ops[i++] = PUSH | A;
	while (i < count_b)
		ops[i++] = PUSH | B;
}

static void	ft_clean_swaps(char *ops, int count_a, int count_b)
{
	if (count_a % 2 && count_b % 2)
		ops[0] = SWAP | A | B;
	else if (count_a % 2)
		ops[0] = SWAP | A;
	else if (count_b % 2)
		ops[0] = SWAP | B;
}

static void	ft_clean_rotate(char *ops, int action, int count_a, int count_b)
{
	int	i;

	i = 0;
	while (i < (count_a * (count_a <= count_b)
			+ count_b * (count_b < count_a)))
		ops[i++] = action | A | B;
	while (i < count_a)
		ops[i++] = action | A;
	while (i < count_b)
		ops[i++] = action | B;
}

static int	ft_clean_consecutive(char *ops, char action)
{
	int	i;
	int	count_a;
	int	count_b;

	count_a = 0;
	count_b = 0;
	i = 0;
	while (ops[i] && !(ops[i] & (SWAP + PUSH + ROT + REV - action)))
	{
		if ((ops[i] ^ action) == A)
			count_a++;
		if ((ops[i] ^ action) == B)
			count_b++;
		ops[i] = 64;
		i++;
	}
	if (action & PUSH)
		ft_clean_push(ops, count_a, count_b);
	else if (action & SWAP)
		ft_clean_swaps(ops, count_a, count_b);
	else if ((action & ROT) || (action & REV))
		ft_clean_rotate(ops, action, count_a, count_b);
	return (i);
}

static int	ft_clean_mixed(char *ops)
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
	// 1 2 3 4 0:
	// rra
	(void)ops;
	return (0);
}

void	ft_optimize_ops(t_ps *data)
{
	int	i;

	i = 0;
	while (data->ops[i])
	{
		i += ft_clean_consecutive(&data->ops[i], PUSH);
		i += ft_clean_consecutive(&data->ops[i], SWAP);
		i += ft_clean_consecutive(&data->ops[i], ROT);
		i += ft_clean_consecutive(&data->ops[i], REV);
		i += ft_clean_mixed(&data->ops[i]);
	}
}
