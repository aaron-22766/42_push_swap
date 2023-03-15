/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:41:07 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/15 13:28:08 by arabenst         ###   ########.fr       */
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
	char	argv[] = "./push_swap, 1, 2, 3";

	data = ft_init_data();
	ft_load_input(argv);
}

START_TEST(push1_1)
{
	int	a[] = {1, 2};
	int	b[] = {0};

	ft_push(data->a, data->b);
	ft_check_valid(a, sizeof(a)/sizeof(int), 0, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

START_TEST(push1_2)
{
	int	a[] = {2};
	int	b[] = {1, 0};

	ft_push(data->a, data->b);
	ft_push(data->a, data->b);
	ft_check_valid(a, sizeof(a)/sizeof(int), 0, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

START_TEST(push1_3)
{
	int	a[] = {};
	int	b[] = {2, 1, 0};

	ft_push(data->a, data->b);
	ft_push(data->a, data->b);
	ft_push(data->a, data->b);
	ft_check_valid(a, sizeof(a)/sizeof(int), 0, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

static void	data_setup2(void)
{
	char	argv[] = "./push_swap, 29551, 23244, 15662, 20439, 91011, 45030, 71706, 55650, -4475, -2306, -5331, 1186, 61811, 4341, 3850, 45012, 52150, 77327, 8287, 34061";

	data = ft_init_data();
	ft_load_input(argv);
}

START_TEST(push2_1)
{
	int	a[] = {10, 9, 7, 8, 19, 13, 17, 15, 1, 2, 0, 3, 16, 5, 4, 12, 14, 18, 6, 11};
	int	b[] = {};

	ft_push(data->a, data->b);
	ft_push(data->b, data->a);
	ft_check_valid(a, sizeof(a)/sizeof(int), 0, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

START_TEST(push2_2)
{
	int	a[] = {10, 9, 7, 8, 19, 13, 17, 15, 1, 2, 0, 3, 16, 5, 4, 12, 14, 18, 6, 11};
	int	b[] = {};

	ft_push(data->a, data->b);
	ft_push(data->a, data->b);
	ft_push(data->b, data->a);
	ft_push(data->b, data->a);
	ft_check_valid(a, sizeof(a)/sizeof(int), 0, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

START_TEST(push2_3)
{
	int	a[] = {11};
	int	b[] = {6, 18, 14, 12, 4, 5, 16, 3, 0, 2, 1, 15, 17, 13, 19, 8, 7, 9, 10};
	int	i;

	i = -1;
	while (++i < 50)
		ft_push(data->a, data->b);
	ft_push(data->b, data->a);
	ft_check_valid(a, sizeof(a)/sizeof(int), 0, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

static void	data_setup3(void)
{
	char	argv[] = "./push_swap, 7, 8, 11, 13, -11, 16, -74, 23, 29, 32, 33, 35, 37, 40, 48, 51, -50, 62, 63, 71, 73, 77, 81, 85, 100, -30, -79, -35, -40, -3, -83, -76, -51, -93, -26, -67, -4, -6, -41, 43, -7, -64, -55, -36, -62, -100, 70, -48, -98, -27";

	data = ft_init_data();
	ft_load_input(argv);
}

START_TEST(push3_1)
{
	int	a[] = {};
	int	b[] = {19, 1, 13, 43, 0, 9, 16, 10, 8, 22, 38, 14, 23, 24, 7, 20, 2, 11, 5, 3, 25, 15, 17, 4, 18, 49, 48, 47, 46, 45, 44, 42, 41, 12, 40, 39, 37, 36, 35, 34, 33, 32, 31, 6, 30, 21, 29, 28, 27, 26};
	int	i;

	i = -1;
	while (++i < 25)
		ft_push(data->a, data->b);
	i = -1;
	while (++i < 5)
		ft_push(data->b, data->a);
	i = -1;
	while (++i < 40)
		ft_push(data->a, data->b);
	i = -1;
	while (++i < 100)
		ft_push(data->a, data->b);
	ft_check_valid(a, sizeof(a)/sizeof(int), 0, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

START_TEST(push3_2)
{
	int	a[] = {18, 4, 17, 15, 25, 3, 5, 11, 2, 20, 7, 24, 23, 14, 38, 22, 8, 10, 16, 9, 0, 43, 13, 1, 19};
	int	b[] = {49, 48, 47, 46, 45, 44, 42, 41, 12, 40, 39, 37, 36, 35, 34, 33, 32, 31, 6, 30, 21, 29, 28, 27, 26};
	int	i;

	i = -1;
	while (++i < 5)
		ft_push(data->a, data->b);
	i = -1;
	while (++i < 50)
		ft_push(data->b, data->a);
	i = -1;
	while (++i < 40)
		ft_push(data->a, data->b);
	i = -1;
	while (++i < 15)
		ft_push(data->b, data->a);
	ft_check_valid(a, sizeof(a)/sizeof(int), 0, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

START_TEST(push3_3)
{
	int	a[] = {};
	int	b[] = {19, 1, 13, 43, 0, 9, 16, 10, 8, 22, 38, 14, 23, 24, 7, 20, 2, 11, 5, 3, 25, 15, 17, 4, 18, 49, 48, 47, 46, 45, 44, 42, 41, 12, 40, 39, 37, 36, 35, 34, 33, 32, 31, 6, 30, 21, 29, 28, 27, 26};
	int	i;

	i = -1;
	while (++i < 49)
		ft_push(data->a, data->b);
	i = -1;
	while (++i < 24)
		ft_push(data->b, data->a);
	i = -1;
	while (++i < 25)
		ft_push(data->a, data->b);
	ft_check_valid(a, sizeof(a)/sizeof(int), 0, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

Suite	*push_suite(void)
{
	Suite	*s;
	TCase	*tc1;
	TCase	*tc2;
	TCase	*tc3;

	s = suite_create("Push");
	
	tc1 = tcase_create("Case 1");
	tcase_add_checked_fixture(tc1, data_setup1, data_teardown);
	tcase_add_test(tc1, push1_1);
	tcase_add_test(tc1, push1_2);
	tcase_add_test(tc1, push1_3);
	suite_add_tcase(s, tc1);
	
	tc2 = tcase_create("Case 2");
	tcase_add_checked_fixture(tc2, data_setup2, data_teardown);
	tcase_add_test(tc2, push2_1);
	tcase_add_test(tc2, push2_2);
	tcase_add_test(tc2, push2_3);
	suite_add_tcase(s, tc2);
	
	tc3 = tcase_create("Case 3");
	tcase_add_checked_fixture(tc3, data_setup3, data_teardown);
	tcase_add_test(tc3, push3_1);
	tcase_add_test(tc3, push3_2);
	tcase_add_test(tc3, push3_3);
	suite_add_tcase(s, tc3);
	
	return (s);
}
