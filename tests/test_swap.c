/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:41:07 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/08 10:50:14 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

// static void	ft_compare_int_arrays(int* expected, int* actual, int size)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < size)
// 		ck_assert_int_eq(expected[i], actual[i]);
// }

// static void	ft_check_input(int *expected, char *argv, int size)
// {
// 	char	**split;
// 	int		i;

// 	split = ft_split(argv, ',');
// 	i = 0;
// 	while (split[i])
// 		i++;
// 	ft_get_input(data, i, split);
// 	i = 0;
// 	while (split[i])
// 		free(split[i++]);
// 	free(split);
// 	ck_assert_ptr_null(data->split);
// 	ck_assert_ptr_nonnull(data->a);
// 	ck_assert_ptr_nonnull(data->b);
// 	ck_assert_ptr_nonnull(data->a->stack);
// 	ck_assert_ptr_nonnull(data->b->stack);
// 	ck_assert_int_eq(data->a->count, size);
// 	ck_assert_int_eq(data->b->count, 0);
// 	ck_assert_int_eq(data->a->top, 0);
// 	ck_assert_int_eq(data->a->top, 0);
// 	ft_compare_int_arrays(expected, data->a->stack, size);
// }

static void	data_setup(void)
{
	data = ft_init_data();
}

static void	data_teardown(void)
{
	ft_free_data(data);
	data = 0;
}

START_TEST(init_data)
{
	ck_assert_ptr_nonnull(data);
}	END_TEST

Suite	*swap_suite(void)
{
	Suite	*s;
	TCase	*tc;

	s = suite_create("Swap");
	tc = tcase_create("Swap");
	tcase_add_checked_fixture(tc, data_setup, data_teardown);
	tcase_add_test(tc, init_data);
	suite_add_tcase(s, tc);
	return (s);
}
