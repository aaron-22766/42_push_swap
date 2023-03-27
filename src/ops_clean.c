/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:23:09 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/27 09:37:39 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_insert_swap(char *ops, char st, int rev)
{
	int	count;
	int	i;

	count = -1;
	i = -1;
	while (ops[++i] && ++count < 3)
	{
		while (ops[i] == CLEAR)
			i++;
		if (count == 0)
			ops[i] = rev * (REV | st) + !rev * CLEAR;
		else if (count == 1)
			ops[i] = SWAP | st;
		else if (count == 2)
			ops[i] = !rev * (ROT | st) + rev * CLEAR;
	}
}

void	ft_replace_manual_swap(char *ops, char st)
{
	int	rev;
	int	count;
	int	i;

	rev = 0;
	count = 0;
	i = -1;
	while (ops[++i] && count < 3)
	{
		if (count == 1 && ops[i] == (REV | st))
			rev = 1;
		if ((count == 0 && ops[i] == (PUSH | (A + B - st)))
			|| (count == 1 && (ops[i] == (ROT | st) || ops[i] == (REV | st)))
			|| (count == 2 && ops[i] == (PUSH | st)))
			count++;
		else if (ops[i] != CLEAR)
			count = 10;
	}
	if (count == 3)
		ft_insert_swap(ops, st, rev);
}

static void	ft_replace_r(char *ops, char op, int count_st)
{
	int	count_r;
	int	i;
	int	j;

	if (ops[0] != op)
		return ;
	count_r = 0;
	i = -1;
	while (ops[++i] == op || ops[i] == CLEAR)
		if (ops[i] == op)
			count_r++;
	j = 0;
	while (count_r > count_st / 2 && j != i)
	{
		if (count_r != count_st)
			ops[j++] = op ^ (ROT | REV) + 0 * count_r++;
		else
			ops[j++] = CLEAR;
	}
}

void	ft_too_many_rotations(t_ps *data, char *ops)
{
	static char	action;
	int			count_a;
	int			i;

	count_a = data->a->size;
	i = -1;
	while (ops[++i])
	{
		count_a += -(ops[i] == (PUSH | B)) + (ops[i] == (PUSH | A));
		if ((ops[i] == (PUSH | B)) || (ops[i] == (PUSH | A)))
			continue ;
		if (((count_a == 2 && (ops[i] == (SWAP | A) || ops[i] == (ROT | A)))
				|| (data->a->size - count_a == 2 && (ops[i] == (SWAP | B)
						|| ops[i] == (ROT | B)))) && (++action <= 2))
		{
			ops[i] = (action * ROT) | ((ops[i] | (SWAP | ROT)) ^ (SWAP | ROT));
			ft_optimize_ops(data, ops);
			return ;
		}
		ft_replace_r(&ops[i], ROT | A, count_a);
		ft_replace_r(&ops[i], REV | A, count_a);
		ft_replace_r(&ops[i], ROT | B, data->a->size - count_a);
		ft_replace_r(&ops[i], REV | B, data->a->size - count_a);
	}
}
