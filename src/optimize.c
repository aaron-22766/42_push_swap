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

int	*ft_decrement_count(int count[4], int r, int rr)
{
	int	temp[2];

	temp[0] = !count[r];
	temp[1] = !count[rr];
	count[0] -= (temp[1] && count[0]);
	count[1] -= (temp[0] && count[1]);
	count[2] -= (temp[1] && count[2]);
	count[3] -= (temp[0] && count[3]);
	return (count);
}

static void	ft_recreate_rot(char *ops, int count[4])
{
	int	i;
	int	temp;
	int	r;

	temp = count[0];
	count[0] = (count[0] - count[1]) * (count[0] > count[1]);
	count[1] = (count[1] - temp) * (count[1] > temp);
	temp = count[2];
	count[2] = (count[2] - count[3]) * (count[2] > count[3]);
	count[3] = (count[3] - temp) * (count[3] > temp);
	i = 0;
	r = 0;
	while (r < 3)
	{
		while (count[r] || count[r + 1])
		{
			while (ops[i] != CLEAR)
				i++;
			ops[i++] = !count[r] * (REV | (A * !!count[1]) | (B * !!count[3]))
				+ !count[r + 1] * (ROT | (A * !!count[0]) | (B * !!count[2]));
			count = ft_decrement_count(count, 0, 1);
		}
		r += 2;
	}
}

// count[0] -> ra
// count[1] -> rra
// count[2] -> rb
// count[3] -> rrb
static void	ft_clean_rot(char *ops)
{
	char	vis;
	int		count[4];
	int		i;

	vis = 0;
	i = 4;
	while (i > 0)
		count[--i] = 0;
	while (ops[i] && !(ops[i] & PUSH) && !(ops[i] & vis))
	{
		if ((ops[i] & ROT) && (ops[i] & A))
			count[0]++;
		if ((ops[i] & REV) && (ops[i] & A))
			count[1]++;
		if ((ops[i] & ROT) && (ops[i] & B))
			count[2]++;
		if ((ops[i] & REV) && (ops[i] & B))
			count[3]++;
		if ((REV | ROT) & ops[i])
			ops[i] = CLEAR;
		else if (ops[i] != CLEAR)
			vis |= ops[i];
		i++;
	}
	ft_recreate_rot(ops, count);
}

void	ft_optimize_ops(char *ops)
{
	char	*prev;
	char	_do;
	int		i;

	prev = 0;
	_do = -1;
	while (!(++_do) || ft_strncmp(ops, prev, !!_do * ft_strlen(ops)))
	{
		free(prev);
		prev = ft_strdup(ops);
		i = -1;
		while (ops[++i])
		{
			if (ops[i] & PUSH)
				ft_clean_push(&ops[i]);
			if (ops[i] & SWAP)
				ft_clean_swap(&ops[i]);
			if (ops[i] & (ROT | REV))
				ft_clean_rot(&ops[i]);
		}
	}
	free(prev);
}
