/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_runner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:11:29 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/09 16:20:13 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	ft_run_suite(Suite *s)
{
	SRunner	*runner;

	runner = srunner_create(s);
	srunner_run_all(runner, CK_NORMAL);
	srunner_free(runner);
	ft_printf("\n");
}

int main(void)
{
	Suite		*(*suites[])(void) = {
		&input_suite,
		&swap_suite,
		&push_suite,
		&rotate_suite
	};
	unsigned long	i;

	ft_printf("\n");
	data = NULL;
	i = 0;
	while (i < (sizeof(suites) / sizeof(Suite *)))
		ft_run_suite((*suites[i++])());
	return (0);
}
