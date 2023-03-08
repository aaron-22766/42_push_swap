/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:55:55 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/08 13:51:28 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_push_swap	*ft_init_data(void)
{
	t_push_swap	*data;

	data = malloc(sizeof(t_push_swap));
	if (!data)
		ft_exit_free(data, 1);
	data->a = malloc(sizeof(t_stack));
	data->b = malloc(sizeof(t_stack));
	if (!data->a || !data->b)
		ft_exit_free(data, 1);
	data->a->stack = 0;
	data->a->count = 0;
	data->a->top = 0;
	data->b->stack = 0;
	data->b->count = 0;
	data->b->top = 0;
	data->split = 0;
	return (data);
}

static void	ft_check_valid_number(t_push_swap *data, char *str)
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
			ft_exit_free(data, 1);
		if (ft_strchr("-+", str[i]) && (!ft_strchr("0123456789", str[i + 1])
				|| (i > 0 && str[i - 1] != ' ')))
			ft_exit_free(data, 1);
	}
	num = ft_atoi(str);
	if (i - first_non_zero > 9 && (num == -1 || num == 0))
		ft_exit_free(data, 1);
	i = -1;
	while (++i < data->a->top)
		if (data->a->stack[i] == num)
			ft_exit_free(data, 1);
}

static void	ft_count_input(t_push_swap *data, int argc, char **argv)
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
				data->a->count++;
		}
		if (empty)
			ft_exit_free(data, 1);
		data->a->count++;
	}
}

void	ft_get_input(t_push_swap *data, int argc, char **argv)
{
	int	i;
	int	j;

	ft_count_input(data, argc, argv);
	data->a->stack = malloc(sizeof(int) * data->a->count);
	data->b->stack = malloc(sizeof(int) * data->a->count);
	if (!data->a->stack || !data->b->stack)
		ft_exit_free(data, 1);
	i = 0;
	while (++i < argc)
	{
		data->split = ft_split(argv[i], ' ');
		j = -1;
		while (data->split[++j])
		{
			ft_check_valid_number(data, data->split[j]);
			data->a->stack[data->a->top++] = ft_atoi(data->split[j]);
		}
		ft_free_split(data);
	}
	if (data->a->count < 2)
		ft_exit_free(data, 0);
	data->a->top = 0;
}
