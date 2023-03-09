/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:41:07 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/09 14:33:26 by arabenst         ###   ########.fr       */
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

START_TEST(push1_1)
{
	int	a[] = {};
	int	b[] = {};

	ft_check_valid(,,,,,);
}	END_TEST

// START_TEST(push1_2)
// {
// 	int	a[] = {};
// 	int	b[] = {};

// 	ft_check_valid(,,,,,);
// }	END_TEST

// START_TEST(push1_3)
// {
// 	int	a[] = {};
// 	int	b[] = {};

// 	ft_check_valid(,,,,,);
// }	END_TEST

// static void	data_setup2(void)
// {
// 	char	argv[] = "./push_swap, 29551, 23244, 15662, 20439, 91011, 45030, 71706, 55650, -4475, -2306, -5331, 1186, 61811, 4341, 3850, 45012, 52150, 77327, 8287, 34061";

// 	data = ft_init_data();
// 	ft_load_input(argv);
// }

// START_TEST(push2_1)
// {
// 	int	a[] = {};
// 	int	b[] = {};

// 	ft_check_valid(,,,,,);
// }	END_TEST

// START_TEST(push2_2)
// {
// 	int	a[] = {};
// 	int	b[] = {};

// 	ft_check_valid(,,,,,);
// }	END_TEST

// START_TEST(push2_3)
// {
// 	int	a[] = {};
// 	int	b[] = {};

// 	ft_check_valid(,,,,,);
// }	END_TEST

// static void	data_setup3(void)
// {
// 	char	argv[] = "./push_swap, 123456, 789, 0";

// 	data = ft_init_data();
// 	ft_load_input(argv);
// }

// START_TEST(push3_1)
// {
// 	int	a[] = {};
// 	int	b[] = {};

// 	ft_check_valid(,,,,,);
// }	END_TEST

// START_TEST(push3_2)
// {
// 	int	a[] = {};
// 	int	b[] = {};

// 	ft_check_valid(,,,,,);
// }	END_TEST

// START_TEST(push3_3)
// {
// 	int	a[] = {};
// 	int	b[] = {};

// 	ft_check_valid(,,,,,);
// }	END_TEST

Suite	*push_suite(void)
{
	Suite	*s;
	TCase	*tc1;
	// TCase	*tc2;
	// TCase	*tc3;

	s = suite_create("Push");
	
	tc1 = tcase_create("Case 1");
	tcase_add_checked_fixture(tc1, data_setup1, data_teardown);
	tcase_add_test(tc1, push1_1);
	// tcase_add_test(tc1, push1_2);
	// tcase_add_test(tc1, push1_3);
	suite_add_tcase(s, tc1);
	
	// tc2 = tcase_create("Case 2");
	// tcase_add_checked_fixture(tc2, data_setup2, data_teardown);
	// tcase_add_test(tc2, push2_1);
	// tcase_add_test(tc2, push2_2);
	// tcase_add_test(tc2, push2_3);
	// suite_add_tcase(s, tc2);
	
	// tc3 = tcase_create("Case 3");
	// tcase_add_checked_fixture(tc3, data_setup3, data_teardown);
	// tcase_add_test(tc3, push3_1);
	// tcase_add_test(tc3, push3_2);
	// tcase_add_test(tc3, push3_3);
	// suite_add_tcase(s, tc3);
	
	return (s);
}
