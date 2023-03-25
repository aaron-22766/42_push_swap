/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:23:09 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/25 17:18:25 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	{
		ops[0] = rev * (REV | st) + !rev * CLEAR;
		ops[1] = SWAP | st;
		ops[2] = !rev * (ROT | st) + rev * CLEAR;
	}
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

static void	ft_replace_r(char *ops, char op, int count_a)
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
	while (count_r > count_a / 2 && j != i)
	{
		if (count_r != count_a)
		{
			count_r++;
			ops[j++] = op ^ (ROT | REV);
		}
		else
			ops[j++] = CLEAR;
	}
}

void	ft_too_many_rotations(t_ps *data, char *ops)
{
	int	count_a;
	int	i;

	count_a = data->a->size;
	i = -1;
	while (ops[++i])
	{
		count_a += -(ops[i] == (PUSH | B)) + (ops[i] == (PUSH | A));
		if ((ops[i] == (PUSH | B)) || (ops[i] == (PUSH | A)))
			continue ;
		ft_replace_r(&ops[i], ROT | A, count_a);
		ft_replace_r(&ops[i], REV | A, count_a);
		ft_replace_r(&ops[i], ROT | B, data->a->size - count_a);
		ft_replace_r(&ops[i], REV | B, data->a->size - count_a);
	}
}
