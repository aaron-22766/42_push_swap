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

static void	ft_clean_push(char *ops)
{
	int	count_a;
	int	count_b;
	int	i;

	count_a = 0;
	count_b = 0;
	i = 0;
	while ((ops[i] & PUSH) || ops[i] == CLEAR)
	{
		if (ops[i] & A)
			count_a++;
		if (ops[i] & B)
			count_b++;
		ops[i++] = CLEAR;
	}
	i = -1;
	while (++i < ((count_a - count_b) * (count_a > count_b)
			+ (count_b - count_a) * (count_b > count_a)))
		ops[i] = (PUSH | A) * (count_a > count_b)
			+ (PUSH | B) * (count_b > count_a);
}

static void	ft_clean_swap(char *ops)
{
	int		count_a;
	int		count_b;
	char	vis;
	int		i;

	count_a = 0;
	count_b = 0;
	vis = 0;
	i = 0;
	while (ops[i] && !(ops[i] & PUSH) && !(ops[i] & vis))
	{
		if ((ops[i] & SWAP) && (ops[i] & A))
			count_a++;
		if ((ops[i] & SWAP) && (ops[i] & B))
			count_b++;
		if (ops[i] & SWAP)
			ops[i] = CLEAR;
		else if (ops[i] != CLEAR)
			vis |= ops[i];
		i++;
	}
	if (count_a + count_b && (count_a % 2 + count_b % 2))
		ops[0] = SWAP | (A * (count_a % 2)) | (B * (count_b % 2));
}

int	*ft_count_helper(int count[4], int r, int temp0, int temp1)
{
	if (r > 4)
	{
		count[0] += ((r & ROT) && (r & A));
		count[1] += ((r & REV) && (r & A));
		count[2] += ((r & ROT) && (r & B));
		count[3] += ((r & REV) && (r & B));
		return (count);
	}
	else if (r == -1)
	{
		count[0] = (count[0] - count[1]) * (count[0] > count[1]);
		count[1] = (count[1] - temp0) * (count[1] > temp0);
		count[2] = (count[2] - count[3]) * (count[2] > count[3]);
		count[3] = (count[3] - temp1) * (count[3] > temp1);
		return (count);
	}
	count[0] -= (temp1 && count[0]);
	count[1] -= (temp0 && count[1]);
	count[2] -= (temp1 && count[2]);
	count[3] -= (temp0 && count[3]);
	return (count);
}

// count[0] -> ra
// count[1] -> rra
// count[2] -> rb
// count[3] -> rrb
static void	ft_clean_rot(char *ops, char vis, int i, int r)
{
	int	count[4];

	while (i > 0)
		count[--i] = 0;
	while (ops[i] && !(ops[i] & PUSH) && !(ops[i] & vis))
	{
		ft_count_helper(count, ops[i++], 0, 0);
		if ((REV | ROT) & ops[i - 1])
			ops[i - 1] = CLEAR;
		else if (ops[i - 1] != CLEAR)
			vis |= ops[i - 1];
	}
	ft_count_helper(count, -1, count[0], count[2]);
	i = 0;
	while (++r < 2 && r++ < 2)
	{
		while (count[r] || count[r + 1])
		{
			while (ops[i] != CLEAR)
				i++;
			ops[i++] = !count[r] * (REV | (A * !!count[1]) | (B * !!count[3]))
				+ !count[r + 1] * (ROT | (A * !!count[0]) | (B * !!count[2]));
			ft_count_helper(count, r, !count[r], !count[r + 1]);
		}
	}
}

void	ft_optimize_ops(t_ps *data, char *ops)
{
	char	*prev;
	int		i;
	char	_do;

	prev = 0;
	i = -1;
	_do = -1;
	while (!(++_do) || ft_strncmp(ops, prev, !!_do * ft_strlen(ops)))
	{
		free(prev);
		prev = ft_strdup(ops);
		while (ops[++i])
		{
			ft_replace_manual_swap(&ops[i], A);
			ft_replace_manual_swap(&ops[i], B);
			if (ops[i] & PUSH)
				ft_clean_push(&ops[i]);
			if (ops[i] & SWAP)
				ft_clean_swap(&ops[i]);
			if (ops[i] & (ROT | REV))
				ft_clean_rot(&ops[i], 0, 4, -2);
		}
	}
	free(prev);
	ft_too_many_rotations(data, ops);
}
