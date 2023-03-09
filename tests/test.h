/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:12:07 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/09 14:29:20 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include "check.h"
# include "../src/push_swap.h"

/* ************************************************************************** */
/*                              GLOBAL VARIABLES                              */
/* ************************************************************************** */

t_push_swap	*data;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// helper.c
void	ft_compare_int_arrays(int* expected, int* actual, int size);
void	ft_check_valid(int *a, int size_a, int top_a,
						int *b, int size_b, int top_b);
char	**ft_get_split(char *argv, int splits);
ssize_t	test_putstr_fd(char *s, int fd);

// Suites
Suite	*input_suite(void);
Suite	*swap_suite(void);
Suite	*push_suite(void);

#endif