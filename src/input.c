/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:55:55 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/22 13:28:32 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_count_input(t_ps *data, int argc, char **argv)
{
	int	empty;
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		empty = 1;
		while (argv[i][j] == ' ')
				j++;
		while (argv[i][++j - 1])
		{
			if (ft_strchr("0123456789", argv[i][j - 1]))
				empty = 0;
			if (argv[i][j - 1] == ' ' && argv[i][j] != ' '
					&& argv[i][j] != '\0')
				data->a->size++;
		}
		if (empty)
			ft_exit(data, 1);
		data->a->size++;
	}
	data->b->size = data->a->size;
}

static void	ft_check_valid_number(t_ps *data, char *str)
{
	int	first_non_zero;
	int	i;
	int	num;

	first_non_zero = 0;
	if (str[first_non_zero] == '+' || str[first_non_zero] == '-')
		first_non_zero++;
	while (str[first_non_zero] == '0')
		first_non_zero++;
	i = -1;
	while (str[++i])
	{
		if (!ft_strchr("0123456789-+ ", str[i]))
			ft_exit(data, 1);
		if (ft_strchr("-+", str[i]) && (!ft_strchr("0123456789", str[i + 1])
				|| (i > 0 && str[i - 1] != ' ')))
			ft_exit(data, 1);
	}
	num = ft_atoi(str);
	if (i - first_non_zero > 9 && (num == -1 || num == 0))
		ft_exit(data, 1);
	i = -1;
	while (++i < data->a->count)
		if (data->b->values[i] == num)
			ft_exit(data, 1);
}

static void	ft_convert_to_order(t_stack *a, t_stack *b)
{
	long long	min;
	long long	lowest;
	int			lowest_index;
	int			i;
	int			j;

	min = LLONG_MIN;
	i = 0;
	while (i < a->count)
	{
		j = -1;
		lowest = LLONG_MAX;
		while (++j < a->count)
		{
			if (b->values[j] < lowest && b->values[j] > min)
			{
				lowest = b->values[j];
				lowest_index = j;
			}
		}
		min = lowest;
		a->values[lowest_index] = i++;
	}
	a->tail = a->count - 1;
}

void	ft_get_input(t_ps *data, int argc, char **argv)
{
	int	i;
	int	j;

	ft_count_input(data, argc, argv);
	data->a->values = malloc(sizeof(int) * data->a->size);
	data->b->values = malloc(sizeof(int) * data->b->size);
	if (!data->a->values || !data->b->values)
		ft_exit(data, 1);
	i = 0;
	while (++i < argc)
	{
		data->split = ft_split(argv[i], ' ');
		j = -1;
		while (data->split[++j])
		{
			ft_check_valid_number(data, data->split[j]);
			data->b->values[data->a->count++] = ft_atoi(data->split[j]);
		}
		ft_free_split(data);
	}
	if (data->a->size < 2)
		ft_exit(data, 0);
	ft_convert_to_order(data->a, data->b);
}
