/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:41:07 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/09 16:32:01 by arabenst         ###   ########.fr       */
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

START_TEST(rotate1_1)
{
	int	a[] = {1, 2, 3};
	int	b[] = {};

	ft_rotate(data->a, 0);
	ft_rotate(data->b, 0);
	ft_check_valid(a, sizeof(a)/sizeof(int), 1, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

START_TEST(rotate1_2)
{
	int	a[] = {1, 2, 3};
	int	b[] = {};

	ft_rotate(data->a, 0);
	ft_rotate(data->a, 0);
	ft_check_valid(a, sizeof(a)/sizeof(int), 2, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

START_TEST(rotate1_3)
{
	int	a[] = {1, 2, 3};
	int	b[] = {};

	ft_rotate(data->a, 0);
	ft_rotate(data->a, 0);
	ft_rotate(data->a, 0);
	ft_rotate(data->b, 0);
	ft_rotate(data->b, 0);
	ft_rotate(data->b, 0);
	ft_check_valid(a, sizeof(a)/sizeof(int), 0, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

static void	data_setup2(void)
{
	char	argv[] = "./push_swap, 29551, 23244, 15662, 20439, 91011, 45030, 71706, 55650, -4475, -2306, -5331, 1186, 61811, 4341, 3850, 45012, 52150, 77327, 8287, 34061";

	data = ft_init_data();
	ft_load_input(argv);
}

START_TEST(rotate2_1)
{
	int	a[] = {29551, 23244, 15662, 20439, 91011, 45030, 71706, 55650, -4475, -2306, -5331, 1186, 61811, 4341, 3850, 45012, 52150, 77327, 8287, 34061};
	int	b[] = {};
	int	i;

	i = -1;
	while (++i < 1)
		ft_rotate(data->a, 0);
	ft_check_valid(a, sizeof(a)/sizeof(int), 1, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

START_TEST(rotate2_2)
{
	int	a[] = {29551, 23244, 15662, 20439, 91011, 45030, 71706, 55650, -4475, -2306, -5331, 1186, 61811, 4341, 3850, 45012, 52150, 77327, 8287, 34061};
	int	b[] = {};
	int	i;

	i = -1;
	while (++i < 11)
		ft_rotate(data->a, 0);
	ft_check_valid(a, sizeof(a)/sizeof(int), 11, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

START_TEST(rotate2_3)
{
	int	a[] = {29551, 23244, 15662, 20439, 91011, 45030, 71706, 55650, -4475, -2306, -5331, 1186, 61811, 4341, 3850, 45012, 52150, 77327, 8287, 34061};
	int	b[] = {};
	int	i;

	i = -1;
	while (++i < 20)
		ft_rotate(data->a, 0);
	ft_check_valid(a, sizeof(a)/sizeof(int), 0, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

static void	data_setup3(void)
{
	char	argv[] = "./push_swap, -8689793, -18224943, +73435942, -25002843, 44595622, -35181944, -61135732, -82853764";

	data = ft_init_data();
	ft_load_input(argv);
}

START_TEST(reverse_rotate1)
{
	int	a[] = {-8689793, -18224943, +73435942, -25002843, 44595622, -35181944, -61135732, -82853764};
	int	b[] = {};
	int	i;

	i = -1;
	while (++i < 1)
		ft_rotate(data->a, 1);
	ft_rotate(data->b, 1);
	ft_check_valid(a, sizeof(a)/sizeof(int), 7, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

START_TEST(reverse_rotate2)
{
	int	a[] = {-8689793, -18224943, +73435942, -25002843, 44595622, -35181944, -61135732, -82853764};
	int	b[] = {};
	int	i;

	i = -1;
	while (++i < 50)
		ft_rotate(data->a, 1);
	i = -1;
	while (++i < 2)
		ft_rotate(data->a, 0);
	ft_rotate(data->b, 1);
	ft_check_valid(a, sizeof(a)/sizeof(int), 0, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

START_TEST(reverse_rotate3)
{
	int	a[] = {-8689793, -18224943, +73435942, -25002843, 44595622, -35181944, -61135732, -82853764};
	int	b[] = {};
	int	i;

	i = -1;
	while (++i < 2)
		ft_rotate(data->a, 0);
	i = -1;
	while (++i < 4)
		ft_rotate(data->a, 1);
	i = -1;
	while (++i < 8)
		ft_rotate(data->a, 0);
	i = -1;
	while (++i < 16)
		ft_rotate(data->a, 1);
	ft_rotate(data->b, 1);
	ft_check_valid(a, sizeof(a)/sizeof(int), 6, b, sizeof(b)/sizeof(int), 0);
}	END_TEST

Suite	*rotate_suite(void)
{
	Suite	*s;
	TCase	*tc1;
	TCase	*tc2;
	TCase	*tc3;

	s = suite_create("Rotate");
	
	tc1 = tcase_create("Rotate1");
	tcase_add_checked_fixture(tc1, data_setup1, data_teardown);
	tcase_add_test(tc1, rotate1_1);
	tcase_add_test(tc1, rotate1_2);
	tcase_add_test(tc1, rotate1_3);
	suite_add_tcase(s, tc1);
	
	tc2 = tcase_create("Rotate2");
	tcase_add_checked_fixture(tc2, data_setup2, data_teardown);
	tcase_add_test(tc2, rotate2_1);
	tcase_add_test(tc2, rotate2_2);
	tcase_add_test(tc2, rotate2_3);
	suite_add_tcase(s, tc2);
	
	tc3 = tcase_create("Reverse_Rotate");
	tcase_add_checked_fixture(tc3, data_setup3, data_teardown);
	tcase_add_test(tc3, reverse_rotate1);
	tcase_add_test(tc3, reverse_rotate2);
	tcase_add_test(tc3, reverse_rotate3);
	suite_add_tcase(s, tc3);

	return (s);
}
