/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:41:07 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/09 16:06:56 by arabenst         ###   ########.fr       */
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
	int	a[] = {2, 3};
	int	b[] = {1};

	ft_push(data->a, data->b);
	ft_check_valid(a, sizeof(a)/sizeof(int), 0, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

START_TEST(push1_2)
{
	int	a[] = {3};
	int	b[] = {2, 1};

	ft_push(data->a, data->b);
	ft_push(data->a, data->b);
	ft_check_valid(a, sizeof(a)/sizeof(int), 0, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

START_TEST(push1_3)
{
	int	a[] = {};
	int	b[] = {3, 2, 1};

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
	int	a[] = {29551, 23244, 15662, 20439, 91011, 45030, 71706, 55650, -4475, -2306, -5331, 1186, 61811, 4341, 3850, 45012, 52150, 77327, 8287, 34061};
	int	b[] = {};

	ft_push(data->a, data->b);
	ft_push(data->b, data->a);
	ft_check_valid(a, sizeof(a)/sizeof(int), 0, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

START_TEST(push2_2)
{
	int	a[] = {29551, 23244, 15662, 20439, 91011, 45030, 71706, 55650, -4475, -2306, -5331, 1186, 61811, 4341, 3850, 45012, 52150, 77327, 8287, 34061};
	int	b[] = {};

	ft_push(data->a, data->b);
	ft_push(data->a, data->b);
	ft_push(data->b, data->a);
	ft_push(data->b, data->a);
	ft_check_valid(a, sizeof(a)/sizeof(int), 0, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

START_TEST(push2_3)
{
	int	a[] = {34061};
	int	b[] = {8287, 77327, 52150, 45012, 3850, 4341, 61811, 1186, -5331, -2306, -4475, 55650, 71706, 45030, 91011, 20439, 15662, 23244, 29551};
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
	int	b[] = {-27, -98, -48, 70, -100, -62, -36, -55, -64, -7, 43, -41, -6, -4, -67, -26, -93, -51, -76, -83, -3, -40, -35, -79, -30, 100, 85, 81, 77, 73, 71, 63, 62, -50, 51, 48, 40, 37, 35, 33, 32, 29, 23, -74, 16, -11, 13, 11, 8, 7};
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
	int	a[] = {-30, -79, -35, -40, -3, -83, -76, -51, -93, -26, -67, -4, -6, -41, 43, -7, -64, -55, -36, -62, -100, 70, -48, -98, -27};
	int	b[] = {100, 85, 81, 77, 73, 71, 63, 62, -50, 51, 48, 40, 37, 35, 33, 32, 29, 23, -74, 16, -11, 13, 11, 8, 7};
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
	int	b[] = {-27, -98, -48, 70, -100, -62, -36, -55, -64, -7, 43, -41, -6, -4, -67, -26, -93, -51, -76, -83, -3, -40, -35, -79, -30, 100, 85, 81, 77, 73, 71, 63, 62, -50, 51, 48, 40, 37, 35, 33, 32, 29, 23, -74, 16, -11, 13, 11, 8, 7};
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
