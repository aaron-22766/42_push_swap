/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:14:05 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/27 14:50:20 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_ps	*ft_init_data(void)
{
	t_ps	*data;

	data = malloc(sizeof(t_ps));
	if (!data)
		ft_exit(data, 1);
	data->a = malloc(sizeof(t_stack));
	data->b = malloc(sizeof(t_stack));
	if (!data->a || !data->b)
		ft_exit(data, 1);
	data->a->values = NULL;
	data->a->head = HEAD;
	data->a->tail = TAIL;
	data->a->count = 0;
	data->a->size = 0;
	data->b->values = NULL;
	data->b->head = HEAD;
	data->b->tail = TAIL;
	data->b->count = 0;
	data->b->size = 0;
	data->ops = NULL;
	data->split = NULL;
	return (data);
}

void	ft_print_ops(char *ops)
{
	int		i;
	char	op;

	i = -1;
	while (ops[++i])
	{
		op = ops[i];
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

int	main(int argc, char **argv)
{
	t_ps	*data;

	if (argc == 1)
		return (0);
	data = ft_init_data();
	ft_get_input(data, argc, argv);
	ft_sort(data);
	ft_optimize_ops(data, data->ops);
	ft_print_ops(data->ops);
	ft_exit(data, 0);
}
