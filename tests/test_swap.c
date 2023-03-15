/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:41:07 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/15 13:30:53 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static void	ft_load_input(char *argv)
{
	char	**split;
	int		splits;
	int		i;

	splits = ft_count_chars(argv, ',') + 1;
	split = ft_get_split(argv, splits);
	if (!split)
	{
		ft_printf("Allocation Error!\n");
		exit(1);
	}
	ft_get_input(data, splits, split);
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

static void	data_teardown(void)
{
	ft_free_data(data);
	data = 0;
}

static void	data_setup1(void)
{
	char	argv[] = "./push_swap, 1, 2, 3, 4, 5, 6";

	data = ft_init_data();
	ft_load_input(argv);
}

START_TEST(swap1_1)
{
	int	a[] = {1, 0, 2, 3, 4, 5};
	int	b[] = {};
	int	top_a;

	top_a = 0;
	data->a->top = top_a;
	ft_swap(data->a);
	ft_check_valid(a, sizeof(a) / sizeof(int), top_a, b, 0, 0);
}	END_TEST

START_TEST(swap1_2)
{
	int	a[] = {0, 2, 1, 3, 4, 5};
	int	b[] = {};
	int	top_a;

	top_a = 1;
	data->a->top = top_a;
	ft_swap(data->a);
	ft_check_valid(a, sizeof(a) / sizeof(int), top_a, b, 0, 0);
}	END_TEST

START_TEST(swap1_3)
{
	int	a[] = {5, 1, 2, 3, 4, 0};
	int	b[] = {};
	int	top_a;

	top_a = 5;
	data->a->top = top_a;
	ft_swap(data->a);
	ft_check_valid(a, sizeof(a) / sizeof(int), top_a, b, 0, 0);
}	END_TEST

static void	data_setup2(void)
{
	char	argv[] = "./push_swap, 29551, 23244, 15662, 20439, 91011, 45030, 71706, 55650, -4475, -2306, -5331, 1186, 61811, 4341, 3850, 45012, 52150, 77327, 8287, 34061";

	data = ft_init_data();
	ft_load_input(argv);
}

START_TEST(swap2_1)
{
	int	a[] = {9, 10, 7, 8, 19, 13, 17, 15, 1, 2, 0, 3, 16, 5, 4, 12, 14, 18, 6, 11};
	int	b[] = {};
	int	top_a;

	top_a = 0;
	data->a->top = top_a;
	ft_swap(data->a);
	ft_check_valid(a, sizeof(a) / sizeof(int), top_a, b, 0, 0);
}	END_TEST

START_TEST(swap2_2)
{
	int	a[] = {10, 9, 7, 8, 19, 13, 17, 15, 1, 2, 3, 0, 16, 5, 4, 12, 14, 18, 6, 11};
	int	b[] = {};
	int	top_a;

	top_a = 10;
	data->a->top = top_a;
	ft_swap(data->a);
	ft_check_valid(a, sizeof(a) / sizeof(int), top_a, b, 0, 0);
}	END_TEST

START_TEST(swap2_3)
{
	int	a[] = {11, 9, 7, 8, 19, 13, 17, 15, 1, 2, 0, 3, 16, 5, 4, 12, 14, 18, 6, 10};
	int	b[] = {};
	int	top_a;

	top_a = 19;
	data->a->top = top_a;
	ft_swap(data->a);
	ft_check_valid(a, sizeof(a) / sizeof(int), top_a, b, 0, 0);
}	END_TEST

static void	data_setup3(void)
{
	char	argv[] = "./push_swap, 123456, 789, 0";

	data = ft_init_data();
	ft_load_input(argv);
}

START_TEST(swap3_1)
{
	int	a[] = {0, 1};
	int	b[] = {2};

	ft_push(data->a, data->b);
	ft_swap(data->a);
	ft_check_valid(a, sizeof(a) / sizeof(int), 0, b, sizeof(b) / sizeof(int), 0);
}	END_TEST

START_TEST(swap3_2)
{
	int	a[] = {0};
	int	b[] = {1, 2};

	ft_push(data->a, data->b);
	ft_push(data->a, data->b);
	ft_swap(data->a);
	ft_check_valid(a, sizeof(a) / sizeof(int), 0, b, sizeof(b) / sizeof(int), 0);
}	END_TEST

START_TEST(swap3_3)
{
	int	a[] = {};
	int	b[] = {0, 1, 2};

	ft_push(data->a, data->b);
	ft_push(data->a, data->b);
	ft_push(data->a, data->b);
	ft_swap(data->a);
	ft_check_valid(a, sizeof(a) / sizeof(int), 0, b, sizeof(b) / sizeof(int), 0);
}	END_TEST

Suite	*swap_suite(void)
{
	Suite	*s;
	TCase	*tc1;
	TCase	*tc2;
	TCase	*tc3;

	s = suite_create("Swap");
	
	tc1 = tcase_create("Case 1");
	tcase_add_checked_fixture(tc1, data_setup1, data_teardown);
	tcase_add_test(tc1, swap1_1);
	tcase_add_test(tc1, swap1_2);
	tcase_add_test(tc1, swap1_3);
	suite_add_tcase(s, tc1);
	
	tc2 = tcase_create("Case 2");
	tcase_add_checked_fixture(tc2, data_setup2, data_teardown);
	tcase_add_test(tc2, swap2_1);
	tcase_add_test(tc2, swap2_2);
	tcase_add_test(tc2, swap2_3);
	suite_add_tcase(s, tc2);
	
	tc3 = tcase_create("Case 3");
	tcase_add_checked_fixture(tc3, data_setup3, data_teardown);
	tcase_add_test(tc3, swap3_1);
	tcase_add_test(tc3, swap3_2);
	tcase_add_test(tc3, swap3_3);
	suite_add_tcase(s, tc3);
	
	return (s);
}
