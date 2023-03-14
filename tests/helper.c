/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:12:56 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/14 16:16:05 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	ft_compare_int_arrays(int *expected, int *actual, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		ck_assert_int_eq(expected[i], actual[i]);
}

void	ft_check_valid(int *a, int size_a, int top_a,
						int *b, int size_b, int top_b)
{
	ck_assert_ptr_nonnull(data->queue);
	ck_assert_int_eq(data->q_size, 2);
	ck_assert_ptr_null(data->split);
	ck_assert_ptr_nonnull(data->a);
	ck_assert_ptr_nonnull(data->b);
	ck_assert_ptr_nonnull(data->a->stack);
	ck_assert_ptr_nonnull(data->b->stack);
	ck_assert_int_eq(data->a->count, size_a);
	ck_assert_int_eq(data->b->count, size_b);
	ck_assert_int_eq(data->a->top, top_a);
	ck_assert_int_eq(data->b->top, top_b);
	ft_compare_int_arrays(a, data->a->stack, size_a);
	ft_compare_int_arrays(b, data->b->stack, size_b);
}

char	**ft_get_split(char *argv, int splits)
{
	char	**result;
	char	**split;
	int		i;
	int		s;
	int		r;

	result = ft_calloc(splits + 1, sizeof(char *));
	if (!result)
		return (NULL);
	split = ft_split(argv, ',');
	i = 0;
	s = 0;
	r = 0;
	while (!i || argv[i - 1])
	{
		if (argv[i] == ',' || !argv[i])
		{
			if (i > 0 && argv[i - 1] != ',')
				result[r++] = split[s++];
			else
				result[r++] = ft_strdup("");
		}
		i++;
	}
	free(split);
	return (result);
}

ssize_t	putstr_ignored(char *s, int fd)
{
	(void)s;
	(void)fd;
	return (0);
}
